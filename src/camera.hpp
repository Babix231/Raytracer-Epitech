/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** camera
*/

#pragma once
#include "ray.hpp"
#include "utils.h"

class camera {
    public:
        camera(int width, int height,vec3 lookfrom,vec3 lookat,vec3 vup,double vfov)
        {
            auto theta = utils::math::degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = width / (double)height * viewport_height;
            auto w = unit_vector(lookfrom - lookat);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);
            _width = width;
            _vfov = vfov;
            _vup = vup;
            _height = height;
            origin = lookfrom;
            _lookat = lookat;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }

        ray get_ray(double s, double t) const {
            return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        }
        void setlookat(vec3 lookAt) {
            _lookat =lookAt;
        }
        vec3 getlookat() {
            return _lookat;
        }
        void setWidth(int width) {
            auto theta = utils::math::degrees_to_radians(_vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = width / _height * viewport_height;
            auto w = unit_vector(origin - _lookat);
            auto u = unit_vector(cross(_vup, w));
            auto v = cross(w, u);
            _width = width;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }
        void setHeight(int height) {
            auto theta = utils::math::degrees_to_radians(_vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = _width / (double)height * viewport_height;
            auto w = unit_vector(origin - _lookat);
            auto u = unit_vector(cross(_vup, w));
            auto v = cross(w, u);
            _height = height;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }
        void setPos(vec3 lookfrom) {
            auto theta = utils::math::degrees_to_radians(_vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = _width / (double)_height * viewport_height;
            auto w = unit_vector(lookfrom - _lookat);
            auto u = unit_vector(cross(_vup, w));
            auto v = cross(w, u);
            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }
        vec3 getPos() {return origin;}
        int getWidth() {return _width;}
        int getHeight() {return _height;}
    private:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 _vup;
        vec3 _lookat;
        vec3 _lookfrom;
        int _width;
        int _height;
        double _vfov;
};