#ifndef POLYGONH
#define POLYGONH

#include <iostream>
#include <vector>

#include "surface.h"

/*
 * Arbitrary convex polygon. Provide points
 * in counter-clockwise orientation about
 * the normal.
 */
class polygon: public surface {
    std::vector<vec3> w;
    std::vector<double> b;

    public:
        vec3 normal;
        double bias;
        material* mat;

        polygon() {}

        polygon(const std::vector<vec3>& p, material* m) {
            int n = p.size();

            if (n < 3) {
                std::cerr << "Polygon has less than three points.\n";
                throw 0;
            }

            normal = unit_vector(cross(p[1] - p[0], p[2] - p[0]));
            bias = dot(normal, p[0]);
            mat = m;

            w = std::vector<vec3>(n);
            b = std::vector<double>(n);

            for (int i = 0; i < n; ++i) {
                w[i] = cross(normal, p[(i+1) % n] - p[i]);
                b[i] = dot(w[i], p[i]);
            }
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
};

bool polygon::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    double d = dot(r.direction(), normal);

    if (-0.0001 < d && d < 0.0001) {
        return false;
    }

    double t = (bias - dot(normal, r.origin())) / d;

    if (t_min < t && t < t_max) {
        vec3 p = r.point_at_parameter(t);

        for (int i = 0; i < w.size(); ++i) {
            if (dot(p, w[i]) < b[i]) {
                return false;
            }
        }

        rec.t = t;
        rec.p = p;
        
        if (dot(r.point_at_parameter(t - 0.00001), normal) > bias) {
            rec.normal = normal;
        } else {
            rec.normal = normal;
        }

        rec.mat_ptr = mat;
        return true;
    }

    return false;
}

#endif
