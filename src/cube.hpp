/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** cube
*/

#pragma once

#include "hitable.hpp"
#include "material.hpp"
namespace RaytracerPrimitives {
class cube : public hittable {
public:
    cube() {}
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    void setPos(vec3 pos);
    vec3 getPos();
    void setMaterial(std::string type, vec3 color);
    std::shared_ptr<material> getMaterial();
    void setProperties(std::map<std::string, std::string> properties);

public:
    vec3 center;
    double size = 1.0;
    std::shared_ptr<material> mat_ptr;
};
}

inline void RaytracerPrimitives::cube::setPos(vec3 pos)
{
    center = pos;
}

inline vec3 RaytracerPrimitives::cube::getPos()
{
    return center;
}

inline void RaytracerPrimitives::cube::setMaterial(std::string type, vec3 color)
{

    if (type == "metal") {
        mat_ptr = std::make_shared<metal>(color);
    } else if (type == "flat") {
        mat_ptr = std::make_shared<flat>(color);
    } else if (type == "dielectric") {
        mat_ptr = std::make_shared<dielectric>(1.0);
    }
}

inline std::shared_ptr<material> RaytracerPrimitives::cube::getMaterial()
{
    return mat_ptr;
}

inline void RaytracerPrimitives::cube::setProperties(std::map<std::string, std::string> properties)
{
    if (properties.count("size")) {
        size = std::stod(properties["size"]);
    }
}

inline bool RaytracerPrimitives::cube::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    double x_min = center.x() - size / 2;
    double x_max = center.x() + size / 2;
    double y_min = center.y() - size / 2;
    double y_max = center.y() + size / 2;
    double z_min = center.z() - size / 2;
    double z_max = center.z() + size / 2;

    double t_x_min = (x_min - r.origin().x()) / r.direction().x();
    double t_x_max = (x_max - r.origin().x()) / r.direction().x();
    double t_y_min = (y_min - r.origin().y()) / r.direction().y();
    double t_y_max = (y_max - r.origin().y()) / r.direction().y();
    double t_z_min = (z_min - r.origin().z()) / r.direction().z();
    double t_z_max = (z_max - r.origin().z()) / r.direction().z();

    double t_min_candidate = std::max({std::min(t_x_min, t_x_max), std::min(t_y_min, t_y_max), std::min(t_z_min, t_z_max), t_min});
    double t_max_candidate = std::min({std::max(t_x_min, t_x_max), std::max(t_y_min, t_y_max), std::max(t_z_min, t_z_max), t_max});

    if (t_min_candidate >= t_max_candidate)
        return false;

    rec.t = t_min_candidate;
    rec.p = r.at(t_min_candidate);

    if (rec.p.x() == x_min)
        rec.normal = vec3(-1, 0, 0);
    else if (rec.p.x() == x_max)
        rec.normal = vec3(1, 0, 0);
    else if (rec.p.y() == y_min)
        rec.normal = vec3(0, -1, 0);
    else if (rec.p.y() == y_max)
        rec.normal = vec3(0, 1, 0);
    else if (rec.p.z() == z_min)
        rec.normal = vec3(0, 0, -1);
    else if (rec.p.z() == z_max)
        rec.normal = vec3(0, 0, 1);

    rec.set_face_normal(r, rec.normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
