#ifndef METALH
#define METALH

#include "material.h"

class metal: public material {
    public:
        vec3 albedo;

        metal(const vec3& a) { albedo = a; }

        virtual bool scatter(const ray& r_in, const hit_record& rec,
                             vec3& attenuation, ray& scattered) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};

#endif
