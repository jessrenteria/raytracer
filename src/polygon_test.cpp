#include <iostream>
#include <vector>

#include "float.h"

#include "util_random.h"
#include "camera.h"
#include "surface_list.h"
#include "sphere.h"
#include "polygon.h"
#include "lambertian.h"
#include "metal.h"

#define MAXDEPTH 50

/*
 * Testing with polygons.
 */

vec3 color(const ray& r, surface* world, int depth) {
    hit_record rec;
    
    if (world->hit(r, 0.001, DBL_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        
        if (depth < MAXDEPTH &&
            rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        } else {
            return vec3(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5*(unit_direction.y() + 1.0);
        return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    const int width = 1200;
    const int height = 600;
    const int ns = 30;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    surface* list[12];
    std::vector<vec3> left_plane = std::vector<vec3>();
    left_plane.push_back(vec3(-0.5, 0.5, -0.5));
    left_plane.push_back(vec3(-0.5, -0.5, -0.5));
    left_plane.push_back(vec3(-0.5, -0.5, -1.5));
    left_plane.push_back(vec3(-0.5, 0.5, -1.5));

    std::vector<vec3> bottom_plane = std::vector<vec3>();
    bottom_plane.push_back(vec3(-0.5, -0.5, 100));
    bottom_plane.push_back(vec3(0.5, -0.5, 100));
    bottom_plane.push_back(vec3(0.5, -0.5, -1.5));
    bottom_plane.push_back(vec3(-0.5, -0.5, -1.5));
    
    std::vector<vec3> right_plane = std::vector<vec3>();
    right_plane.push_back(vec3(0.5, -0.5, -0.5));
    right_plane.push_back(vec3(0.5, 0.5, -0.5));
    right_plane.push_back(vec3(0.5, 0.5, -1.5));
    right_plane.push_back(vec3(0.5, -0.5, -1.5));

    std::vector<vec3> top_plane = std::vector<vec3>();
    top_plane.push_back(vec3(-0.5, 0.5, -0.5));
    top_plane.push_back(vec3(-0.5, 0.5, -1.5));
    top_plane.push_back(vec3(0.5, 0.5, -1.5));
    top_plane.push_back(vec3(0.5, 0.5, -0.5));

    std::vector<vec3> back_plane = std::vector<vec3>();
    back_plane.push_back(vec3(0.5, 0.5, -1.5));
    back_plane.push_back(vec3(-0.5, 0.5, -1.5));
    back_plane.push_back(vec3(-0.5, -0.5, -1.5));
    back_plane.push_back(vec3(0.5, -0.5, -1.5));

    std::vector<vec3> trap = std::vector<vec3>();
    trap.push_back(vec3(0.25, 0.5, 0.1));
    trap.push_back(vec3(0.4, -0.5, 0.1));
    trap.push_back(vec3(-0.4, -0.5, 0.1));
    trap.push_back(vec3(-0.25, 0.5, 0.1));

    list[0] = new polygon(left_plane, new lambertian(vec3(0.8, 0.0, 0.0)));
    list[1] = new polygon(bottom_plane, new lambertian(vec3(0.8, 0.0, 0.0)));
    list[2] = new polygon(right_plane, new lambertian(vec3(0.8, 0.0, 0.0)));
    list[3] = new polygon(top_plane, new lambertian(vec3(0.8, 0.0, 0.0)));
    list[4] = new polygon(back_plane, new lambertian(vec3(0.8, 0.0, 0.0)));
    list[5] = new polygon(trap, new lambertian(vec3(0.22, 0.56, 0.56)));
    list[6] = new sphere(vec3(0, 0, -1), 0.25, new metal(vec3(0.8, 0.8, 0.8)));
    list[7] = new sphere(vec3(-0.4, -0.4, -1), 0.1, new lambertian(vec3(randr(gen), randr(gen), randr(gen))));
    list[8] = new sphere(vec3(0.4, -0.4, -1), 0.1, new lambertian(vec3(randr(gen), randr(gen), randr(gen))));
    list[9] = new sphere(vec3(0, 0.4, -1), 0.1, new lambertian(vec3(randr(gen), randr(gen), randr(gen))));
    list[10] = new sphere(vec3(-0.11, 0.35, 0.1), 0.05, new lambertian(vec3(0, 0, 0)));
    list[11] = new sphere(vec3(0.11, 0.35, 0.1), 0.05, new lambertian(vec3(0, 0, 0)));

    surface* world = new surface_list(list, 12);
    camera cam;

    for (int y = height-1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            vec3 col(0, 0, 0);

            for (int i = 0; i < ns; ++i) {
                double u = double(x + randr(gen)) / double(width);
                double v = double(y + randr(gen)) / double(height);
                col += color(cam.get_ray(u, v), world, 0);
            }

            col /= double(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}
