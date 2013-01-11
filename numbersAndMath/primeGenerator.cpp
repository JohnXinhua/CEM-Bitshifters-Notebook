const int MAX = 10000; // never bigger than 10^7
bool isPrime[MAX];
int primes[MAX]; // list of primes up to max
int cp;
void generatePrimes() {
    memset(isPrime, true, sizeof(isPrime));
    primes[0] = 2;
    cp = 1;
    for (int i = 3; i < MAX; i+=2) {
        if (isPrime[i]) {
            primes[cp++] = i;
            for (unsigned long long j = i*i; j < MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }
}
