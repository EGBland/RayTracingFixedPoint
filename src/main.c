#include <stdio.h>
#include "fixed_point.h"
#include "vec3.h"

#define TEST_FP 0
#define TEST_INVSQRT 0
#define TEST_VEC3 0

#define image_width 256
#define image_height 224

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
    fp_t a, b, c;
    a = to_fp(322);
    printf("fp\t\t%d\t", a);
    print_bin(a);
    printf("\nmsb\t\t%d", msb(a));
    b = fp_sqrt(a);
    printf("\nsqrt\t\t%d\t", b);
    print_bin(b);
    c = fp_invsqrt(a);
    printf("\ninvsqrt\t\t%d\t", c);
    print_bin(c);
    printf("\n");
    return 0;

#elif TEST_VEC3 == 1
    fp_t a;
    vec3_t v1, v2;
    v1.x = 13*FP_ONE;
    v1.y = 12*FP_ONE;
    v1.z = 3*FP_ONE;
    printf("vec3\t(%d,%d,%d)\n", v1.x, v1.y, v1.z);
    a = vec3_dot(&v1, &v1);
    printf("len\t%d\n", a);
    vec3_norm(&v2, &v1);
    printf("norm\t(%d,%d,%d)\n", v2.x, v2.y, v2.z);
    a = vec3_dot(&v2, &v2);
    printf("nlen\t%d\n", a);
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