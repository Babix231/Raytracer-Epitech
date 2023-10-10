/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** cylindre
*/

#pragma once

#include "hitable.hpp"
#include "material.hpp"
namespace RaytracerPrimitives {
class cylindre : public hittable {
    public:
        cylindre() {}
        bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const;
    void setPos(vec3 pos);
    vec3 getPos();
    void setMaterial(std::string type, vec3 color);
    std::shared_ptr<material> getMaterial();
    void setProperties(std::map<std::string, std::string> properties);
    public:
        vec3 center;
        double radius = 1.0;
        double height = 2.0;
        vec3 axis = vec3(1, 0, 0);
        std::shared_ptr<material> mat_ptr;
};
};
inline void RaytracerPrimitives::cylindre::setPos(vec3 pos)
{
    center = pos;
}

inline vec3 RaytracerPrimitives::cylindre::getPos()
{
    return center;
}

inline void RaytracerPrimitives::cylindre::setMaterial(std::string type, vec3 color)
{
    if (type == "metal") {
        mat_ptr = std::make_shared<metal>(color);
    } else if (type == "flat") {
        mat_ptr = std::make_shared<flat>(color);
    } else if (type == "dielectric") {
        mat_ptr = std::make_shared<dielectric>(4.0);
    }
}

inline std::shared_ptr<material> RaytracerPrimitives::cylindre::getMaterial()
{
    return mat_ptr;
}

inline void RaytracerPrimitives::cylindre::setProperties(std::map<std::string, std::string> properties)
{
    if (properties.find("axis") != properties.end()) {
        if (properties["axis"] == "1.000000")
            axis = vec3(1, 0, 0);
        else if (properties["axis"] == "2.000000")
            axis = vec3(0, 1, 0);
        else if (properties["axis"] == "3.000000")
            axis = vec3(0, 0, 1);
    }
    if (properties.find("radius") != properties.end())
        radius = std::stod(properties["radius"]);
    if (properties.find("height") != properties.end())
        height = std::stod(properties["height"]);
}

inline bool RaytracerPrimitives::cylindre::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared() - pow(dot(r.direction(), axis), 2);
    auto b = dot(oc, r.direction()) - dot(oc, axis) * dot(r.direction(), axis);
    auto c = oc.length_squared() - pow(dot(oc, axis), 2) - pow(radius, 2);

    auto discriminant = pow(b, 2) - a * c;
    if (discriminant < 0) return false;

    auto sqrtd = sqrt(discriminant);
    auto root = (-b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    vec3 p = r.at(root);
    vec3 n = unit_vector(p - center - dot(p - center, axis) * axis);

    if (dot(p - center, axis) > height || dot(p - center, axis) < 0) {
        root = (-b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
        p = r.at(root);
        n = unit_vector(p - center - dot(p - center, axis) * axis);
        if (dot(p - center, axis) > height || dot(p - center, axis) < 0)
            return false;
    }

    rec.t = root;
    rec.p = p;
    rec.normal = n;
    rec.mat_ptr = mat_ptr;
    rec.set_face_normal(r, n);
    return true;
}
