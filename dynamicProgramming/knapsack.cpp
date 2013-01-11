int favor[110];
int price[110];
int n, budget;
int dp[110][10500];

int knapsack() {
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= n; i++) {
		for (int w = 1; w <= budget; w++) {
			dp[i][w] = dp[i-1][w];			// value without adding this item
			if (price[i] <= w) {			// can i fit it?
				int curr = favor[i];		// value of current item
				curr += dp[i-1][w-price[i]];	// fill remaining space
				if (dp[i][w] < curr) {		// should i add this item?
					dp[i][w] = curr;		// keep the item!
				}
			}
		}
	}
	return dp[n][budget];
}

int exactKnapsack() {
	memset(dp, -1, sizeof(dp));

	for (int i = 1; i <= n; i++) {
		for (int w = 1; w <= budget; w++) {
			dp[i][w] = dp[i-1][w];
			if (price[i] == w) {
				if (dp[i][w] == -1 || dp[i][w] < favor[i]) {
					dp[i][w] = favor[i];
				}
			} else if (w > price[i] && dp[i-1][w-price[i]] != -1) {
				int curr = favor[i] + dp[i-1][w-price[i]];
				if (dp[i][w] == -1 || dp[i][w] < curr) {
					dp[i][w] = curr;
				}
			}
		}
	}

	// search for best answer in valid range
	int best = 0;
	for (int w = 0; w <= budget; w++) if (best < dp[n][w]) best = dp[n][w];
	return best;
}
