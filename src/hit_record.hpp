/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** hit_record
*/

#pragma once
#include "ray.hpp"
#include "vec3.hpp"
class material;
struct hit_record {
    vec3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};