#include <stdio.h>
#include "fixed_point.h"
#define TEST_FP 0
#define TEST_INVSQRT 1

const int image_width = 256;
const int image_height = 224;

const fp_t image_width_fp = to_fp(image_width);
const fp_t image_height_fp = to_fp(image_height);
const fp_t max_colour_fp = to_fp(255);

void print_bin(int n) {
    int i;
    for(i = 31; i >= 0; i--) {
        printf("%d", (n>>i)&1);
    }
}

int main() {
    // fp test
#if TEST_FP == 1
    fp_t a,b,c;
    a = fp_div(to_fp(123),to_fp(10));
    b = fp_div(to_fp(457),to_fp(10));
    printf("fp 12.3\t\t%d\t", a);
    print_bin(a);
    printf("\nfp 45.7\t\t%d\t", b);
    print_bin(b);
    printf("\nfp 12.3*45.7\t%d\t",fp_mult(a,b));
    print_bin(fp_mult(a,b));
    printf("\n12.3*45.7\t%d\t", from_fp(fp_mult(a,b)));
    print_bin(from_fp(fp_mult(a,b)));
    printf("\n");
    return 0;

#elif TEST_INVSQRT == 1
    fp_t a,b;
    a = to_fp(7853);
    printf("fp 7853\t\t%d\t", a);
    print_bin(a);
    b = fp_invsqrt(a);
    printf("\nfp sqrt(7853)\t%d\t", b);
    print_bin(b);
    printf("\n");
    return 0;

#else
    int x, y;
    fp_t xf, yf;
    fp_t rf, gf, bf;
    int r, g, b;

    printf("P3\n%d\t%d\n255\n", image_width, image_height);
    
    for(y = image_height - 1; y >= 0; y--) {
        for(x = 0; x < image_width; x++) {
            xf = to_fp(x);
            yf = to_fp(y);
            rf = fp_mult(xf,max_colour_fp);
            rf = fp_idiv(rf, image_width_fp);
            gf = fp_mult(yf,max_colour_fp);
            gf = fp_idiv(gf, image_height_fp);
            bf = to_fp(127);

            r = from_fp(rf);
            g = from_fp(gf);
            b = from_fp(bf);

            printf("%d\t%d\t%d\n", r, g, b);
        }
    }
#endif
}