/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** light
*/

#pragma once

#include "vec3.hpp"

class Light {
public:
    Light() = default;
    Light(const vec3& position, const vec3& ambient_intensity, const vec3& diffuse_intensity, const vec3& specular_intensity)
        : _position(position), _ambient_intensity(ambient_intensity), _diffuse_intensity(diffuse_intensity), _specular_intensity(specular_intensity) {}

    virtual ~Light() = default;

    virtual vec3 get_direction(const vec3& point) const = 0;

    vec3 get_position() const { return _position; }

    vec3 get_ambient_intensity() const { return _ambient_intensity; }

    vec3 get_diffuse_intensity() const { return _diffuse_intensity; }

    vec3 get_specular_intensity() const { return _specular_intensity; }

private:
    vec3 _position;
    vec3 _ambient_intensity;
    vec3 _diffuse_intensity;
    vec3 _specular_intensity;
};

class DirectionalLight : public Light {
public:
    DirectionalLight() = default;
    DirectionalLight(const vec3& direction, const vec3& ambient_intensity, const vec3& diffuse_intensity, const vec3& specular_intensity)
        : Light(vec3(0, 0, 0), ambient_intensity, diffuse_intensity, specular_intensity), _direction(unit_vector(-direction)) {}

    vec3 get_direction(const vec3& /*point*/) const override { return _direction; }

private:
    vec3 _direction;
};

class PointLight : public Light {
public:
    PointLight() = default;
    PointLight(const vec3& position, const vec3& ambient_intensity, const vec3& diffuse_intensity, const vec3& specular_intensity)
        : Light(position, ambient_intensity, diffuse_intensity, specular_intensity) {}

    vec3 get_direction(const vec3& point) const override { return unit_vector(get_position() - point); }
};

class SpotLight : public Light {
public:
    SpotLight() = default;
    SpotLight(const vec3& position, const vec3& ambient_intensity, const vec3& diffuse_intensity, const vec3& specular_intensity, const vec3& direction, float cut_off_angle)
        : Light(position, ambient_intensity, diffuse_intensity, specular_intensity), _direction(unit_vector(-direction)), _cut_off_angle(cut_off_angle) {}

    vec3 get_direction(const vec3& point) const override { return unit_vector(get_position() - point); }

    float get_cut_off_angle() const { return _cut_off_angle; }

private:
    vec3 _direction;
    float _cut_off_angle;
};
