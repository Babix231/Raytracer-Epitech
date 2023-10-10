/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** plane
*/

#pragma once
#include "hitable.hpp"
#include "material.hpp"

namespace RaytracerPrimitives {
class plane : public hittable {
   public:
    plane() {}
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    void setPos(vec3 pos);
    vec3 getPos();
    void setMaterial(std::string type, vec3 color);
    std::shared_ptr<material> getMaterial();
    void setProperties(std::map<std::string, std::string> properties);

   public:
    vec3 center;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
};
};  // namespace RaytracerPrimitives

inline void RaytracerPrimitives::plane::setPos(vec3 pos) { center = pos; }

inline vec3 RaytracerPrimitives::plane::getPos() { return center; }

inline void RaytracerPrimitives::plane::setMaterial(std::string type,
                                                    vec3 color) {
    if (type == "metal") {
        mat_ptr = std::make_shared<metal>(color);
    } else if (type == "flat") {
        mat_ptr = std::make_shared<flat>(color);
    } else if (type == "dielectric") {
        mat_ptr = std::make_shared<dielectric>(4.0);
    }
}

inline std::shared_ptr<material> RaytracerPrimitives::plane::getMaterial() {
    return mat_ptr;
}

inline void RaytracerPrimitives::plane::setProperties(
    std::map<std::string, std::string> properties) {
    normal = vec3(0, 1, 0);
    if (properties.find("axis") != properties.end()) {
        if (properties["axis"] == "3.000000")
            normal = vec3(1, 0, 0);
        else if (properties["axis"] == "1.000000")
            normal = vec3(0, 1, 0);
        else if (properties["axis"] == "2.000000")
            normal = vec3(0, 0, 1);
    }
}

inline bool RaytracerPrimitives::plane::hit(const ray& r, double t_min,
                                            double t_max,
                                            hit_record& rec) const {
    auto denom = dot(normal, r.direction());
    if (denom > -0.0001 && denom < 0.0001) {
        return false;
    }
    auto point = center;
    auto t = dot(point - r.origin(), normal) / denom;
    if (t < t_min || t > t_max) {
        return false;
    }
    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
