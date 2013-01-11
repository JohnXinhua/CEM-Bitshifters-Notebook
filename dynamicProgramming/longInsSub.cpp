int seq[4040]; int dyn[4040]; int n;

int lis() { // longest increasing subsequence for sequence seq of length n - O(nlgn)
	// for longest decreasing subsequence, multiply elements by -1
	// for longest common subsequence with unique elements, map to order of first string and do lis

	int size = 1;
	dyn[0] = seq[0];

	for (int i = 1; i < n; i++) {
		int curr = seq[i];
		int last = dyn[size - 1];
		if (last < curr) {
			dyn[size] = curr;
			size++;
		} else if (last > curr) {
			int *place = lower_bound(dyn, dyn + size, curr); // binsearch from <algorithm>
			if (*place > curr) *place = curr;
		}
	}
	return size;
}
