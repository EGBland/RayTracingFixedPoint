#ifndef __VEC3_H_DEFINED__
#define __VEC3_H_DEFINED__ 1

#include "fixed_point.h"

typedef struct vec3_t {
    fp_t x, y, z;
} vec3_t;

void vec3_add(vec3_t*, vec3_t*, vec3_t*);
void vec3_mult(vec3_t*, fp_t, vec3_t*);
fp_t vec3_dot(vec3_t*, vec3_t*);
void vec3_norm(vec3_t*, vec3_t*);

#endif