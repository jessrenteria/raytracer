#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;

        camera() {
            origin = vec3(0.0, 0.0, 0.0);
            lower_left_corner = vec3(-2.0, -1.0, -1.0);
            horizontal = vec3(4.0, 0.0, 0.0);
            vertical = vec3(0.0, 2.0, 0.0);
        }

        camera(vec3 o, vec3 llc, vec3 h, vec3 v) {
            origin = o;
            lower_left_corner = llc;
            horizontal = h;
            vertical = v;
        }

        ray get_ray(double u, double v) {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }
};

#endif
