#include "fixed_point.h"

#define NR_ITERATIONS 6

// for significand 12
const int __y0s[32] = {
	5,		// m=19 (0.0014)
	8,		// m=18 (0.0020)
	11,		// m=17 (0.0028)
	16,		// m=16 (0.0039)
	22,		// m=15 (0.0055)
	32,		// m=14 (0.0078)
	45,		// m=13 (0.0110)
	64,		// m=12 (0.0156)
	90,		// m=11 (0.0221)
	128,	// m=10 (0.0312)
	181,	// m=9 (0.0442)
	256,	// m=8 (0.0625)
	362,	// m=7 (0.0884)
	512,	// m=6 (0.1250)
	724,	// m=5 (0.1768)
	1024,	// m=4 (0.2500)
	1448,	// m=3 (0.3536)
	2048,	// m=2 (0.5000)
	2896,	// m=1 (0.7071)
	4096,	// m=0 (1.0000)
	5792,	// m=-1 (1.4142)
	8192,	// m=-2 (2.0000)
	11585,	// m=-3 (2.8284)
	16384,	// m=-4 (4.0000)
	23170,	// m=-5 (5.6569)
	32768,	// m=-6 (8.0000)
	46340,	// m=-7 (11.3137)
	65536,	// m=-8 (16.0000)
	92681,	// m=-9 (22.6274)
	131072,	// m=-10 (32.0000)
	185363,	// m=-11 (45.2548)
	262144,	// m=-12 (64.0000)
};

char msb(int a) {
	char i;
	for (i = 31; i >= 0; i--) {
		if ((a >> i & 1) == 1) return 31-i;
	}
	return -1;
}

fp_t fp_div(fp_t x, fp_t y) {
	int sign,rem,div,quo,b,d,ret;
	sign = 1 << 31;
	rem = x & ~sign;
	div = y & ~sign;

	quo = 0;
	b = SIGNIFICAND+1;

	while(rem && b >= 0) {
		d = rem / div;
		rem %= div;
		quo += d << b;
		rem <<= 1;
		b--;
	}

	ret = quo >> 1;
	ret |= (x & sign) ^ (y & sign);
	return ret;
}

fp_t fp_sqrt(fp_t S) {
	char m, i;
	fp_t x, X;
	const fp_t threehalves = 3 << (SIGNIFICAND - 1);

	m = msb(S);
	if (m == -1) return -1;
	X = __y0s[m];
	x = fp_mult(S,X);

	// iterate
	for (i = 0; i < NR_ITERATIONS; i++) {
		S = fp_mult(S, fp_mult(X, X));
		X = threehalves - (S >> 1);
		x = fp_mult(x, X);
	}
	return x;
}

fp_t fp_invsqrt(fp_t S) {
	char m, i;
	fp_t y,Y;
	const fp_t threehalves = 3 << (SIGNIFICAND - 1);

	// estimate sqrt
	m = msb(S);
	if (m == -1) return -1;
	Y = __y0s[m];
	y = Y;
	
	// iterate
	for (i = 0; i < NR_ITERATIONS; i++) {
		S = fp_mult(S, fp_mult(Y, Y));
		Y = threehalves - (S >> 1);
		y = fp_mult(y, Y);
	}

	return y;
}