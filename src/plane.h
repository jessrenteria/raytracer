#ifndef PLANEH
#define PLANEH

#include "surface.h"

class plane: public surface {
    public:
        vec3 normal;
        double bias;
        material* mat;

        plane() {}

        plane(const vec3& n, double b, material* m) {
            normal = unit_vector(n);
            bias = b;
            mat = m;
        }

        plane(const vec3& n, const vec3& x0, material* m) {
            normal = unit_vector(n);
            bias = dot(normal, x0);
            mat = m;
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
};

bool plane::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    double d = dot(r.direction(), normal);

    if (-0.0001 < d && d < 0.0001) {
        return false;
    }

    double t = (bias - dot(normal, r.origin())) / d;

    if (t_min < t && t < t_max) {
        rec.t = t;
        rec.p = r.point_at_parameter(rec.t);
        rec.normal = normal;
        rec.mat_ptr = mat;
        return true;
    }

    return false;

    // dot(normal, r.origin()) + dot(normal, t*r.direction()) + bias = 0
    // dot(normal, r.origin()) + t*dot(normal, r.direction()) = -bias
    // t = (-d - dot(normal, r.origin())) / dot(normal, r.direction())
}

#endif
