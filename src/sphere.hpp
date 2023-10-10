/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** sphere
*/

#pragma once
#include "material.hpp"

namespace RaytracerPrimitives {
class sphere : public hittable {
   public:
    sphere() {}
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    void setPos(vec3 pos);
    vec3 getPos();
    void setMaterial(std::string type, vec3 color);
    std::shared_ptr<material> getMaterial();
    void setProperties(std::map<std::string, std::string> properties);

   public:
    vec3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;
};
}  // namespace RaytracerPrimitives

inline void RaytracerPrimitives::sphere::setPos(vec3 pos) { center = pos; }

inline vec3 RaytracerPrimitives::sphere::getPos()
{
    return center;
}

inline void RaytracerPrimitives::sphere::setMaterial(std::string type, vec3 color)
{
    if (type == "metal") {
        mat_ptr = std::make_shared<metal>(color);
    } else if (type == "flat") {
        mat_ptr = std::make_shared<flat>(color);
    } else if (type == "dielectric") {
        mat_ptr = std::make_shared<dielectric>(4.0);
    }
    else{
        mat_ptr = std::make_shared<flat>(vec3(1, 0, 0));
    }
}

inline std::shared_ptr<material> RaytracerPrimitives::sphere::getMaterial()
{
    return mat_ptr;
}

inline void RaytracerPrimitives::sphere::setProperties(std::map<std::string, std::string> properties)
{
    if (properties.find("radius") != properties.end())
        radius = std::stod(properties["radius"]);
    else
        radius = 1;
}

inline bool RaytracerPrimitives::sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
