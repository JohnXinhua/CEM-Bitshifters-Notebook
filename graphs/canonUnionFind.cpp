#define MAX 1000
int p[MAX], rank[MAX];

void make_set(int x){
	p[x] = x;
	rank[x] = 0;
}

void link(int x, int y) {
	if (rank[x] > rank[y]) {
		p[y] = x;
	} else {
		p[x] = y;
		if (rank[x] == rank[y])
			rank[y] = rank[y] + 1;
	}
}

int find_set(int x) {
	if (x != p[x])
		p[x] = find_set(p[x]);
	return p[x];
}

void union_set(int x, int y) {
	link(find_set(x), find_set(y));
}

bool connected(int x, int y) {
	return find_set(x) == find_set(y);
}
