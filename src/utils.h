/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** rtweekend
*/

#pragma once

#include <limits>

#include "hit_record.hpp"
#include "hitable.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

namespace utils {
        namespace math {
            const double infinity = std::numeric_limits<double>::infinity();
            const double pi = 3.1415926535897932385;

            inline double random_double() { return rand() / (RAND_MAX + 1.0); }

            inline double random_double(double min, double max) {
                return min + (max - min) * random_double();
            }

            inline double degrees_to_radians(double degrees) {
                return degrees * pi / 180.0;
            }

            inline double clamp(double x, double min, double max) {
                if (x < min) return min;
                if (x > max) return max;
                return x;
            }
    };  // namespace math
    inline vec3 pixel_color_variance(const std::vector<vec3>& colors,
                                     const vec3& average_color) {
        vec3 variance(0, 0, 0);
        for (const auto& c : colors) {
            variance += (c - average_color) * (c - average_color);
        }
        variance /= colors.size() - 1;
        return variance;
    }

    inline void write_color(std::ostream& out, vec3 pixel_color,
                            int samples_per_pixel) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        (void)samples_per_pixel;
        // auto scale = 1.0 / samples_per_pixel;
        auto scale = 1.0;
        r = sqrt(scale * (r));
        g = sqrt(scale * (g));
        b = sqrt(scale * (b));
        out << static_cast<int>(256 * utils::math::clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * utils::math::clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * utils::math::clamp(b, 0.0, 0.999)) << '\n';
    }

    inline vec3 ray_color(const ray& r, const hittable& world, int depth) {
        hit_record rec;

        if (depth <= 0)
            return world.hit(r, 0.1, utils::math::infinity, rec)
                       ? rec.mat_ptr->getAlbedo()
                       : vec3(0, 0, 0);
        if (world.hit(r, 0.1, utils::math::infinity, rec)) {
            ray scattered;
            vec3 attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, world, depth - 1);
            return vec3(0, 0, 0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        // do a blue sky gradient
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) +
               t * vec3(0.5, 0.7, 1.0);  // linear interpolation
    }
}  // namespace utils