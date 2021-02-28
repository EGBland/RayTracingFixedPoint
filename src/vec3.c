#include "vec3.h"
#include "fixed_point.h"

void vec3_add(vec3_t* result, vec3_t* v1, vec3_t* v2) {
    result->x = fp_add(v1->x, v2->x);
    result->y = fp_add(v1->y, v2->y);
    result->z = fp_add(v1->z, v2->z);
}

void vec3_mult(vec3_t* result, fp_t lambda, vec3_t* v) {
    result->x = fp_mult(lambda, v->x);
    result->y = fp_mult(lambda, v->y);
    result->z = fp_mult(lambda, v->z);
}

fp_t vec3_dot(vec3_t* v1, vec3_t* v2) {
    return fp_mult(v1->x, v2->x) + fp_mult(v1->y, v2->y) + fp_mult(v1->z, v2->z);
}

void vec3_norm(vec3_t* result, vec3_t* v) {
    fp_t len = vec3_dot(v, v);
    vec3_mult(result, fp_invsqrt(len), v);
}