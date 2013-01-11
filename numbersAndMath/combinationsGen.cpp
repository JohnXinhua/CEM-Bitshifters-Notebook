int pascal[33][33]; // pascal[n][k] is nCk
void genPascal() {
	pascal[0][0] = 1;
	for (int i = 1; i < 32; i++) {
		pascal[i][0] = 1; pascal[i][i] = 1;
		for (int j = 1; j < i; j++) pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
	}
}
