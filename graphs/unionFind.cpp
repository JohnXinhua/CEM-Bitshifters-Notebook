struct adj { int i, j; double distance; };

adj distances[10010];
int parent[110], height[110], n, ndist;

int root(int node) {
	 if (parent[node] == node) return node;
	 return parent[node] = root(parent[node]); // TA-DAH!
}

void connect(int a, int b) {
	int roota = root(a);
	int rootb = root(b);
	if (height[roota] >= height[rootb]) {
		parent[rootb] = roota;
		height[roota] = max(height[roota], height[rootb] + 1);
	} else {
		parent[roota] = rootb;
		height[rootb] = max(height[rootb], height[roota] + 1);
	}
}

double domst() {
	double total = 0;
	for (int d = 0; d < ndist; d++) {
		adj curr = distances[d];
		if (root(curr.i) != root(curr.j)) {
			connect(curr.i, curr.j);
			total += curr.distance;
		}
	}
	return total;
}
