#ifndef SPHEREH
#define SPHEREH

#include "surface.h"

class sphere: public surface {
    public:
        vec3 center;
        double radius;
        material* mat;

        sphere() {}

        sphere(const vec3& c, double r, material* m) {
            center = c;
            radius = r;
            mat = m;
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - a*c;

    if (discriminant > 0) {
        double temp = (-b - sqrt(b*b - a*c)) / a;

        if (t_min < temp && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }

        temp = (-b + sqrt(b*b - a*c)) / a;

        if (t_min < temp && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }

    return false;
}

#endif
