struct node {
	int transPos;		// position in transformed array, init with -1, filled by traverse()
	int height;		// height of node, root has height 0
	vector<int> children;	// remember to clear each new test case
};

node nodes[100010];
int n;					// number of nodes
int trans[200020];
int t;					// number of elements in trans
pair<int, int> m[18][200020];	// value, index

// build transformed tree for lca via special preorder traversal
void traverse(int i) {
	trans[t++] = i;
	if (nodes[i].transPos == -1) nodes[i].transPos = t-1;
	for (vector<int>::iterator it = nodes[i].children.begin(); it < nodes[i].children.end(); it++) {
		traverse(*it);
		trans[t++] = i;
	}
}

void preprocess() {
	t = 0;
	traverse(0);

	// preprocess rmq
	for (int j = 0; j < t; j++) {
		m[0][j] = make_pair(nodes[trans[j]].height, trans[j]);
	}
	for (int i = 1; (1 << i) <= t; i++) {
		for (int j = 0; (1 << i) + j <= t; j++) {
			m[i][j] = min(m[i - 1][j], m[i - 1][j + (1 << (i - 1))]);
		}
	}
}

int lca(int a, int b) {
	// rmq to find lca
	int i, j;
	i = nodes[a].transPos;
	j = nodes[b].transPos;
	if (i > j) swap(i, j);

	int pow = 0;
	while ((1 << (pow + 1)) <= (j - i + 1)) pow++;
	return min(m[pow][i], m[pow][j - (1 << pow) + 1]).second;
}
