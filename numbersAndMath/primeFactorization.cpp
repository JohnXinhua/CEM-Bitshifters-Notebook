int primes[limit]; // list of primes up to sqrt(max_n), generate with seive
int cp; // number of primes
map<int, int> factors; // count of prime factors for each number
void factorize(int n) {
	factors.clear();
	huge curr = n; int i = 0;
	for (int i = 0; i < cp && primes[i]*primes[i] <= n; i++) {
		while (curr % primes[i] == 0) {
			factors[primes[i]] += 1;
			curr /= primes[i];
		}
	}
	if (curr > 1) factors[curr] += 1;
}
