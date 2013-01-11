
int sums[110][110]; int arr[110][110]; int n;
int maxsum() { // O(n³) time, O(n²) space
	memset(sums, 0, sizeof(sums));
	for (int i = 1; i <= n; i++) // create sums array
		for (int j = 1; j <= n; j++)
			sums[i][j] = sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] + arr[i][j];

	int max = -200;
	for (int i = 1; i <= n; i++) {  // find maximal subarray by sweeping rows
		for (int j = i; j <= n; j++) {
			int sum = 0;
			for (int k = 1; k <= n; k++) {
				sum += sums[k][j] - sums[k-1][j] - sums[k][i-1] + sums[k-1][i-1];
				if (max < sum) max = sum;
				if (sum < 0) sum = 0;
			}
		}
	}
	return max;
}
