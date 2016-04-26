#ifndef MATERIALH
#define MATERIALH

#include "ray.h"

class material {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec,
                             vec3& attentuation, ray& scattered) const = 0;
};

#endif
