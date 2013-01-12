int lambda, mu; // lambda is start of cycle, mu is length
bool cycle_finder(sequence[]) {
	lambda = mu = 2 * MAX_CYCLES + 1; // MAX_CYCLES up to 2^29
	for (int i = 0; i <= MAX_CYCLES; i++) {
		if (sequence[2*i + 1] == sequence[i]) {
			for (mu = 1; mu <= i; mu++) {
				if(i % mu != 0) continue;
				if(sequence[2*i + 1 - mu] == sequence[i]) break;
			}
			for (lambda = 0; lambda <= i; lambda++) {
				if(sequence[lambda] == sequence[lambda + mu]) break;
			}
			return true;
		}
	}
	return false;
}
