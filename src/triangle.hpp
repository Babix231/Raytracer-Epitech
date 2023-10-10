/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** triangle
*/

#pragma once
#include "material.hpp"

namespace RaytracerPrimitives {
    class Triangle : public hittable {
        public:
            Triangle();
            Triangle(vec3 a, vec3 b, vec3 c) : _a(a), _b(b), _c(c) {}
            ~Triangle();
            vec3 getA() const {return _a;}
            vec3 getB() const {return _b;}
            vec3 getC() const {return _c;}
            vec3 getColor() const;
            void setA(vec3 a) { _a = a;}
            void setB(vec3 b) { _b = b;}
            void setC(vec3 c) { _c = c;}
            bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const;
            void setMaterial(std::string type, vec3 color);
            std::shared_ptr<material> getMaterial();
            void setProperties(std::map<std::string, std::string> properties);
            void setPos(vec3 pos);
            vec3 getPos();
            void setColor(vec3 color);

           private:
            vec3 _a;
            vec3 _b;
            vec3 _c;
            vec3 _color;
            std::shared_ptr<material> mat_ptr;
    };
}

inline void RaytracerPrimitives::Triangle::setPos(vec3 pos)
{
    _a += pos;
    _b += pos;
    _c += pos;
}

inline vec3 RaytracerPrimitives::Triangle::getPos()
{
    return _a;
}

inline void RaytracerPrimitives::Triangle::setColor(vec3 color)
{
    _color = color;
}

inline vec3 RaytracerPrimitives::Triangle::getColor() const
{
    return _color;
}

inline void RaytracerPrimitives::Triangle::setMaterial(std::string type, vec3 color)
{
    if (type == "metal") {
        mat_ptr = std::make_shared<metal>(color);
    } else if (type == "flat") {
        mat_ptr = std::make_shared<flat>(color);
    } else if (type == "dielectric") {
        mat_ptr = std::make_shared<dielectric>(4.0);
    }
}

inline std::shared_ptr<material> RaytracerPrimitives::Triangle::getMaterial()
{
    return mat_ptr;
}

inline void RaytracerPrimitives::Triangle::setProperties(std::map<std::string, std::string> properties)
{
    vec3 tmpA;
    vec3 tmpB;
    vec3 tmpC;
    // print map
    for (auto const& x : properties)
    {
        std::cout << x.first  // string (key)
                  << ':'
                  << x.second // string's value
                  << std::endl ;
    }
    if (properties.find("vecAx") != properties.end() && properties.find("vecAy") != properties.end() && properties.find("vecAz") != properties.end())
        tmpA = vec3(std::stod(properties["vecAx"]), std::stod(properties["vecAy"]), std::stod(properties["vecAz"]));
    else
        tmpA = vec3(0, 0, 0);
    if (properties.find("vecBx") != properties.end() && properties.find("vecBy") != properties.end() && properties.find("vecBz") != properties.end())
        tmpB = vec3(std::stod(properties["vecBx"]), std::stod(properties["vecBy"]), std::stod(properties["vecBz"]));
    else
        tmpB = vec3(0, 0, 0);
    if (properties.find("vecCx") != properties.end() && properties.find("vecCy") != properties.end() && properties.find("vecCz") != properties.end())
        tmpC = vec3(std::stod(properties["vecCx"]), std::stod(properties["vecCy"]), std::stod(properties["vecCz"]));
    else
        tmpC = vec3(0, 0, 0);
    if (properties.find("scale") != properties.end()) {
        tmpA *= std::stod(properties["scale"]);
        tmpB *= std::stod(properties["scale"]);
        tmpC *= std::stod(properties["scale"]);
    }
    _a = tmpA;
    _b = tmpB;
    _c = tmpC;
}

inline RaytracerPrimitives::Triangle::Triangle()
{
    _a = vec3(0, 0, 0);
    _b = vec3(0, 0, 0);
    _c = vec3(0, 0, 0);
    _color = vec3(0, 0, 0);
}

inline RaytracerPrimitives::Triangle::~Triangle()
{
}

inline bool RaytracerPrimitives::Triangle::hit(const ray& r, double t_min, double t_max,
                                               hit_record& rec) const
{
    vec3 ab = _b - _a;
    vec3 ac = _c - _a;
    vec3 pvec = cross(r.direction(), ac);
    double det = dot(ab, pvec);
    if (det < 0.0000001 && det > -0.0000001)
        return false;
    double invDet = 1 / det;
    vec3 tvec = r.origin() - _a;
    double u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1)
        return false;
    vec3 qvec = cross(tvec, ab);
    double v = dot(r.direction(), qvec) * invDet;
    if (v < 0 || u + v > 1)
        return false;
    double t = dot(ac, qvec) * invDet;
    if (t < t_min || t > t_max)
        return false;
    rec.t = t;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, cross(ab, ac));
    rec.mat_ptr = mat_ptr;
    return true;
}