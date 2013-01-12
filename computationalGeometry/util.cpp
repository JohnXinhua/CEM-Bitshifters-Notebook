double area() {
	double total = 0.0;
	int i, j;

	for(i = 0; i < NumPoints; i++) {
		j = (i+1) % NumPoints;
		total += (points[i].x*points[j].y) – (points[j].x*points[i].y);
	}

	return total / 2;
}

void crossProduct(double v1[3], double v2[3], double* n) {
	n[0] = v1[1] * v2[2] - v1[2] * v2[1];
	n[1] = v1[2] * v2[0] - v1[0] * v2[2];
	n[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
