char a[1010]; char b[1010]; int dyn[1010][1010];
int lcs() { // longest common subsequence between a and b - O(mn)
	int ca = strlen(a);
	int cb = strlen(b);
	for (int i = 1; i <= ca; i++) {
		for (int j = 1; j <= cb; j++) {
			if(a[i-1] == b[j-1])
				dyn[i][j] = 1 + dyn[i-1][j-1];
			else
				dyn[i][j] = max(dyn[i-1][j], dyn[i][j-1]);
		}
	}
	if (ca == 0)  return 0;
	return dyn[ca][cb];
}
