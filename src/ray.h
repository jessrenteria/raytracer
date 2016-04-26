#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray {
    public:
        vec3 a;
        vec3 b;

        ray() {}
        ray(const vec3& _a, const vec3& _b) { a = _a; b = _b; }

        vec3 origin() const { return a; }
        vec3 direction() const { return b; }

        vec3 point_at_parameter(float t) const { return a + t*b; }
};

#endif
