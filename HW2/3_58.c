

int decode2(long x, long y, long z) {
    y = y - z;
    x = x * y;
    long r1 = y;
    r1 = r1 << 63;
    r1 = r1 >> 63;
    r1 = r1 ^ x;
    return r1;
}