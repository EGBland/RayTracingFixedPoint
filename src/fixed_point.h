#ifndef __FIXED_POINT_H_DEFINED__
#define __FIXED_POINT_H_DEFINED__ 1

#define SIGNIFICAND (12)
#define FP_FRAC_MASK (1 << SIGNIFICAND) - 1
#define FP_ONE 1 << SIGNIFICAND

#define to_fp(X) X << SIGNIFICAND
#define from_fp(X) X >> SIGNIFICAND
#define fp_mult(X,Y) (((X >> SIGNIFICAND) * (Y >> SIGNIFICAND)) << SIGNIFICAND) + (X >> SIGNIFICAND) * (Y & FP_FRAC_MASK) + (X & FP_FRAC_MASK) * (Y >> SIGNIFICAND) + (((X & FP_FRAC_MASK) * (Y & FP_FRAC_MASK)) >> SIGNIFICAND)
#define fp_idiv(X,Y) (X / Y) << SIGNIFICAND
#define fp_add(X,Y) X + Y

typedef int fp_t;

fp_t fp_div(fp_t, fp_t);
fp_t fp_sqrt(fp_t);
fp_t fp_invsqrt(fp_t);
#endif