int x[1010], n, m[1000][1000];

void preprocess() {
	for (int j = 0; j < n; j++) {
		m[0][j] = x[j]; // es llenar el [0] con los dudes del arreglo original
	}

	// ahora vamos a ir llenando las potencias subsecuentes de 2
	for (int i = 1; (1 << i) <= n; i++) {
		for (int j = 0; (1 << i) + j <= n; j++) {
			m[i][j] = min(m[i - 1][j], m[i - 1][j + (1 << (i - 1))]); // llenar las potencias de 2
		}
	}
}

int query(int i, int j) {
	int pow = 0;
	while ((1 << (pow + 1)) <= (j - i + 1)) pow++;
	return min(m[pow][i], m[pow][j - (1 << pow) + 1]);
}
