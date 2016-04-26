#ifndef SURFACELISTH
#define SURFACELISTH

#include "surface.h"

class surface_list: public surface {
    public:
        surface** list;
        int list_size;

        surface_list() {}
        surface_list(surface** l, int n) { list =l; list_size = n; }
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
};

bool surface_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record current_rec;
    bool hit_something = false;
    double closest_hit = t_max;

    for (int i = 0; i < list_size; ++i) {
        if (list[i]->hit(r, t_min, closest_hit, current_rec)) {
            hit_something = true;
            closest_hit = current_rec.t;
            rec = current_rec;
        }
    }

    return hit_something;
}

#endif
