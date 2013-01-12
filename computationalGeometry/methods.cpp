struct P { double x, y; P() {}; P(double q, double w) : x(q), y(w) {} };
struct P { int x, y; P() {}; P(int q, int w) : x(q), y(w) {} };
double dist(double ax, double ay, double bx, double by){
  return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
__typeof(P().x) dist2(P p, P q){
  return (p.x - q.x) * (p.x - q.x) - (p.y - q.y) * (p.y - q.y);
}

// Left turn or CCW (this one works with integers)
// Returns true iff the sequence v1->v2->v3 is a left turn in
// the plane. Straight line is not a left turn (change to ">= -C( EPS )").
// #define EPS ... (1e-7 for doubles, 0 for ints)
template<class C>
bool leftTurn(C x1, C y1, C x2, C y2, C x3, C y3 ){
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > C(EPS);
}

// Point inside triangle
// Returns true iff point (xx,yy) is inside the counter-clockwise triangle (x[3],y[3])
// REQUIRES: leftTurn()
bool pointInsideTriangle( double x[], double y[], double xx, double yy ){
	return leftTurn(x[0], y[0], x[1], y[1], xx, yy)
		&& leftTurn(x[1], y[1], x[2], y[2], xx, yy)
		&& leftTurn(x[2], y[2], x[0], y[0], xx, yy);
}

// Polar angle
// Returns an angle in the range [0, 2*Pi) of a given Cartesian point.
// If the point is (0,0), -1.0 is returned.
// REQUIRES: #include <math.h>, #define EPS 0.000000001, P has members x and y.
double polarAngle(P p){
	if (fabs(p.x) <= EPS && fabs(p.y) <= EPS) return -1.0;
	if (fabs(p.x) <= EPS) return (p.y > EPS ? 1.0 : 3.0) * acos(0);
	double theta = atan(1.0 * p.y / p.x);
	if (p.x > EPS) return(p.y >= -EPS ? theta : (4 * acos(0) + theta));
	return 2 * acos(0) + theta;
}

// Point inside polygon
// Returns true iff p is inside poly.
// PRE: The vertices of poly are ordered (either clockwise or counter-clockwise)
// POST: Modify code inside to handle the special case of "on an edge".
// REQUIRES: polarAngle(), #include <math.h>, #include <vector>, #define EPS 0.000000001
bool pointInPoly(P p, vector<P> &poly) {
	int n = poly.size();
	double ang = 0.0;
	for (int i = n - 1, j = 0; j < n; i = j++) {
		P v(poly[i].x - p.x, poly[i].y - p.y);
		P w(poly[j].x - p.x, poly[j].y - p.y);
		double va = polarAngle(v);
		double wa = polarAngle(w);
		double xx = wa - va;
		if (va < -0.5 || wa < -0.5 || fabs(fabs(xx) - 2 * acos(0)) < EPS){
			// POINT IS ON THE EDGE
			assert(false);
			ang += 2 * acos(0);
			continue;
		}
		if (xx < -2 * acos(0)) ang += xx + 4 * acos(0);
		else if (xx > 2 * acos(0)) ang += xx - 4 * acos(0);
		else ang += xx;
	}
	return (ang * ang > 1.0);
}

// Distance from a point to a line
// Returns the distance from p to the line defined by {a, b}.
// The closest point on the line is returned through (cpx, cpy).
// Does not work for degenerate lines (when answer is undefined).
// REQUIRES: #include <math.h>, #define EPS ..., dist()
double distToLine(double ax, double ay, double bx, double by, double px, double py, double *cpx, double *cpy) {
	//Formula: cp = a + (p-a).(b-a) / |b-a| * (b-a)
	double proj = ((px - ax) * (bx - ax) + (py - ay) * (by - ay)) /
				  ((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	*cpx = ax + proj * (bx - ax);
	*cpy = ay + proj * (by - ay);
	return dist(px, py, *cpx, *cpy);
}

// Distance from a point to a line segment
// Returns the distance from p to the line segment ab.
// The closest point on ab is returned through (cpx, cpy).
// Works correctly for degenerate line segments (a == b).
// REQUIRES: #include <math.h>, #define EPS ..., dist(), distToLine()
double distToLineSegment(double ax, double ay, double bx, double by, double px, double py, double *cpx, double *cpy) {
	if ((bx - ax) * (px - ax) + (by - ay) * (py - ay) < EPS) {
		*cpx = ax;
		*cpy = ay;
		return dist(ax, ay, px, py);
	}
	if ((ax - bx) * (px - bx) + (ay - by) * (py - by) < EPS) {
		*cpx = bx;
		*cpy = by;
		return dist(bx, by, px, py);
	}
	return distToLine(ax, ay, bx, by, px, py, cpx, cpy);
}

// Line intersection
// Returns the point of intersection of two lines:
// (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
// Puts the result (x, y) into (r[0], r[1]) and returns true.
// If there is no intersection, return false;
// USED BY: circle3pts
bool lineIntersect(double x[], double y[], double r[]){
	double n[2]; n[0] = y[3] - y[2]; n[1] = x[2] - x[3];
	double denom = n[0] * (x[1] - x[0]) + n[1] * (y[1] - y[0]);
	if (fabs(denom) < EPS ) return false;
	double num = n[0] * (x[0] - x[2]) + n[1] * (y[0] - y[2]);
	double t = -num / denom;
	r[0] = x[0] + t * (x[1] - x[0]);
	r[1] = y[0] + t * (y[1] - y[0]);
	return true;
}

// Line intersection (P version)
// Returns the point of intersection of two lines:
// (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
// Puts the result (x, y) into (r[0], r[1]) and returns true.
// If there is no intersection, return false;
bool lineIntersect(P a, P b, P c, P d, P &r) {
	P n; n.x = d.y - c.y; n.y = c.x - d.x;
	double denom = n.x * (b.x - a.x) + n.y * (b.y - a.y);
	if(fabs(denom) < EPS) return false;
	double num = n.x * (a.x - c.x) + n.y * (a.y - c.y);
	double t = -num / denom;
	r.x = a.x + t * (b.x - a.x);
	r.y = a.y + t * (b.y - a.y);
	return true;
}

// Line segment intersection
// Returns true iff two line segments: (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3])
// intersect. Call lineIntersect(x, y) to get the point of intersection.
// WARNING: Does not work for collinear line segments!
template<class T>
bool lineSegIntersect(vector<T> &x, vector<T> &y) {
	double ucrossv1 = (x[1] - x[0]) * (y[2] - y[0]) - (y[1] - y[0]) * (x[2] - x[0]);
	double ucrossv2 = (x[1] - x[0]) * (y[3] - y[0]) - (y[1] - y[0]) * (x[3] - x[0]);
	if (ucrossv1 * ucrossv2 > 0) return false;
	double vcrossu1 = (x[3] - x[2]) * (y[0] - y[2]) - (y[3] - y[2]) * (x[0] - x[2]);
	double vcrossu2 = (x[3] - x[2]) * (y[1] - y[2]) - (y[3] - y[2]) * (x[1] - x[2]);
	return vcrossu1 * vcrossu2 <= 0;
}

// Circle through 3 points
// Computes the circle containing the 3 given points.
// The 3 points are (x[0], y[0]), (x[1], y[1]) and (x[2], y[2]).
// The centre of the circle is returned as (r[0], r[1]).
// The radius is returned normally. If the circle is undefined (the points are collinear),
// -1.0 is returned.
// REQUIRES: lineIntersect
double circle3pts(double x[], double y[], double r[]) {
	double lix[4], liy[4];
	lix[0] = 0.5 * (x[0] + x[1]); liy[0] = 0.5 * (y[0] + y[1]);
	lix[1] = lix[0] + y[1] - y[0];	liy[1] = liy[0] + x[0] - x[1];
	lix[2] = 0.5 * (x[1] + x[2]); liy[2] = 0.5 * (y[1] + y[2]);
	lix[3] = lix[2] + y[2] - y[1];	liy[3] = liy[2] + x[1] - x[2];
	if (!lineIntersect(lix, liy, r)) return -1.0;
	return sqrt((r[0] - x[0]) * (r[0] - x[0]) + (r[1] - y[0]) * (r[1] - y[0]));
}

// Circle of a given radius through 2 points
// Computes the center of a circle containing the 2 given points. The circle has the given radius.
// The returned center is never to the right of the vector (x1, y1)-->(x2, y2).
// If this is possible, returns true and passes the center through the ctr array. Otherwise, returns false.
bool circle2ptsRad( double x1, double y1, double x2, double y2, double r, double ctr[2] ){
	double d2 = ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
	double det = r * r / d2 - 0.25;
	if( det < 0.0 ) return false;
	double h = sqrt( det );
	ctr[0] = ( x1 + x2 ) * 0.5 + ( y1 - y2 ) * h;
	ctr[1] = ( y1 + y2 ) * 0.5 + ( x2 - x1 ) * h;
	return true;
}
