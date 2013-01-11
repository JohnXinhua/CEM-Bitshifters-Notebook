int gcd(int a, int b) { // greatest common divisor between a and b
    if (a == 0) return b;
    return gcd(b % a, a);
}

int extGcd(int a, int b, int& x, int& y) { // returns d=gcd(a,b) and give x,y such that ax+by=d
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int a1, b1, c, x1, y1, rst;
    a1 = b % a; b1 = a; c = b / a;
    rst = extGcd(a1, b1, x1, y1);
    x = y1 - c * x1; y = x1;
    return rst;
}
