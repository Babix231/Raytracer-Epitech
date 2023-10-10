/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** objfile
*/

#pragma once

#include "material.hpp"
#include "triangle.hpp"

namespace RaytracerPrimitives {
    class Objfile : public hittable {
        public:
            Objfile() = default;
            ~Objfile() = default;
            bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const;
            void setMaterial(std::string type, vec3 color);
            std::shared_ptr<material> getMaterial();
            void setProperties(std::map<std::string, std::string> properties);
            void setPos(vec3 pos);
            vec3 getPos();
            void setTriangles(std::vector<Triangle> triangles) { _triangles = triangles; }
            void setColor(vec3 color);

           private:
           std::vector<Triangle> _triangles;
           std::shared_ptr<material> mat_ptr;
        //    double _scale = 1;
    };
}

inline void RaytracerPrimitives::Objfile::setPos(vec3 pos)
{
    for (auto &triangle : _triangles) {
        triangle.setPos(pos);
    }
}

inline vec3 RaytracerPrimitives::Objfile::getPos()
{
    return _triangles[0].getPos();
}

inline void RaytracerPrimitives::Objfile::setColor(vec3 color)
{
    for (auto &triangle : _triangles) {
        triangle.setColor(color);
    }
}

inline std::shared_ptr<material> RaytracerPrimitives::Objfile::getMaterial()
{
    return mat_ptr;
}

inline void RaytracerPrimitives::Objfile::setMaterial(std::string type, vec3 color)
{
    for (auto& triangle : _triangles) {
        triangle.setMaterial(type, color);
    }
}

inline void RaytracerPrimitives::Objfile::setProperties(std::map<std::string, std::string> properties)
{
    for (auto& triangle : _triangles) {
        triangle.setProperties(properties);
    }
}

inline bool RaytracerPrimitives::Objfile::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    bool hit_anything = false;
    hit_record temp_rec;
    double closest_so_far = t_max;

    for (auto &triangle : _triangles) {
        if (triangle.hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
