/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** material
*/

#pragma once

#include "utils.h"
#include "ray.hpp"
#include "hitable.hpp"
#include "hit_record.hpp"

class material {
    public:
     virtual ~material() = default;
     virtual bool scatter(const ray& r_in, const hit_record& rec,
                          vec3& attenuation, ray& scattered) const = 0;
     virtual vec3 getAlbedo() const = 0;
     virtual void setColor(vec3 color) = 0;
};

class flat : public material {
    public:
        flat(const vec3& a) : albedo(a) {}
        void setColor(vec3 color) override {albedo = color;};

        bool scatter(const ray& r_in, const hit_record& rec,vec3& attenuation,ray& scattered) const override {
            (void)r_in;
            auto scatter_direction = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;

        }
        vec3 getAlbedo() const override { return albedo; }

       public:
        vec3 albedo;
};

class metal : public material {
    public:
        metal(const vec3& a) : albedo(a) {}
        void setColor(vec3 color) override {albedo = color;};

        bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + attenuation * random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
        vec3 getAlbedo() const override { return albedo; }

       public:
        vec3 albedo;
};

class dielectric : public material {
public:
    dielectric(double refraction_index) : ref_idx(refraction_index) {}
    void setColor(vec3 color) override { albedo = color; };
    bool scatter(const ray& r_in, const hit_record& rec,
                         vec3& attenuation, ray& scattered) const override {
        attenuation = vec3(1.0, 1.0, 1.0);
        double etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        if (etai_over_etat * sin_theta > 1.0) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }
    vec3 getAlbedo() const override { return albedo; }
    vec3 albedo;
   private:
    double ref_idx;
    static double schlick(double cosine, double ref_idx) {
        double r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0*r0;
        return r0 + (1 - r0)*pow((1 - cosine), 5);
    }

    static vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
        double cos_theta = dot(-uv, n);
        vec3 r_out_parallel = etai_over_etat * (uv + cos_theta*n);
        vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared())*n;
        return r_out_parallel + r_out_perp;
    }
};
