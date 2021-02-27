#ifndef __FIXED_POINT_H_DEFINED__
#define __FIXED_POINT_H_DEFINED__ 1

#define SIGNIFICAND (8)

#define to_fp(X) X << SIGNIFICAND
#define from_fp(X) X >> SIGNIFICAND
#define fp_imult(X,Y) ((X >> SIGNIFICAND) * (Y >> SIGNIFICAND)) << SIGNIFICAND
#define fp_mult(X,Y) (X >> (SIGNIFICAND / 2)) * (Y >> (SIGNIFICAND / 2))
#define fp_fmult(X,Y) (X * Y) << SIGNIFICAND
#define fp_idiv(X,Y) (X / Y) << SIGNIFICAND
#define fp_add(X,Y) X + Y

typedef int fp_t;

fp_t fp_div(fp_t, fp_t);
fp_t fp_sqrt(fp_t);
fp_t fp_invsqrt(fp_t);
#endif