const int MAX = 14; // up to 16, maybe; if more needed, use malloc for memo array
pair<int, int> coords[MAX];
int n;
double memo[MAX][MAX][1 << MAX];

double distance(pair<int, int> &a, pair<int, int> &b) {
	return hypot(a.first - b.first, a.second - b.second);
}

double dfs(int curr, int start, int visited) {
	if (memo[curr][start][visited] == -1) {
		if (visited == (1 << n) - 1) {
			memo[curr][start][visited] = distance(coords[curr], coords[start]);
		} else {
			double min = -1;
			for (int i = 0; i < n; i++) {
				if (!(visited & (1 << i))) {
					double currDist = dfs(i, start, visited | (1 << i))
						+ distance(coords[curr], coords[i]);
					if (min == -1 || min > currDist) min = currDist;
				}
			}
			memo[curr][start][visited] = min;
		}
	}
	return memo[curr][start][visited];
}

double solve() {
	for (int i = 0; i < n; i++) // clear memo, don't use memset with doubles
		for (int j = 0; j < n; j++)
			for (int k = 0; k < (1 << n); k++)
				memo[i][j][k] = -1;

	double min = -1;
	for (int i = 0; i < n; i++) {
		double dist = dfs(i, i, 1 << i);
		if (min == -1 || min > dist) min = dist;
	}

	return min;
}
