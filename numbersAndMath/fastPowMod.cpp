int fastpowmod(int a, int b, int m) { // calculate (a^b) % m
    int total = 1;
    for (int n = 1, power = a % m; b > 0; n <<= 1, b >>= 1, power = (power * power) % m) {
        if (b & 1 == 1) {
            total = (total * power) % m;
        }
    }
    return total;
}
