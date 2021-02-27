#include "fixed_point.h"

#define NR_ITERATIONS 0

// for significand 8
static const int __y0s[32] = {
	741455,	// m=23
	524288,	// m=22
	370727,	// m=21
	262144,	// m=20
	185363,	// m=19
	131072,	// m=18
	92681,	// m=17
	65536,	// m=16
	46340,	// m=15
	32768,	// m=14
	23170,	// m=13
	16384,	// m=12
	11585,	// m=11
	8192,	// m=10
	5792,	// m=9
	4096,	// m=8
	2896,	// m=7
	2048,	// m=6
	1448,	// m=5
	1024,	// m=4
	724,	// m=3
	512,	// m=2
	362,	// m=1
	256,	// m=0
	181,	// m=-1
	128,	// m=-2
	90, 	// m=-3
	64, 	// m=-4
	45, 	// m=-5
	32, 	// m=-6
	22, 	// m=-7
	16, 	// m=-8
};


char msb(int a) {
    char i;
    for(i = 0; i < 32; i++) {
        if ((a>>i)&1 == 1) return i;
    }
    return 0;
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
    int b,Y,x,y,m,i;

    const fp_t half = 1 << (SIGNIFICAND - 1);
    const fp_t threehalves = 3*half;

    m = msb(S);
    if(m == 0) return 0;

    b = S;
    Y = __y0s[m];
    x = S*Y;
    //y = Y;

    for(i = 0; i < NR_ITERATIONS; i++) {
        b = b*Y*Y;
        Y = threehalves - half*Y;
        x = x*Y;
        //y = y*Y;
    }
    return x;
}

fp_t fp_invsqrt(fp_t S) {
    int b,Y,x,y,m,i;

    const fp_t half = 1 << (SIGNIFICAND - 1);
    const fp_t threehalves = 3*half;

    m = msb(S);
    if(m == 0) return 0;

    b = S;
    Y = __y0s[m];
    //x = S*Y;
    y = Y;

    for(i = 0; i < NR_ITERATIONS; i++) {
        b = b*Y*Y;
        Y = threehalves - half*Y;
        //x = x*Y;
        y = y*Y;
    }
    return y;
}