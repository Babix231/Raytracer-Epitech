/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** hitable
*/

#pragma once
#include <vector>
#include <memory>
#include <map>

#include "ray.hpp"
#include "utils.h"
#include "material.hpp"
#include "hit_record.hpp"

class hittable {
    public:
     virtual ~hittable() = default;
     virtual bool hit(const ray& r, double t_min, double t_max,
                      hit_record& rec) const = 0;
     virtual void setPos(vec3 pos) = 0;
     virtual vec3 getPos() = 0;
     virtual void setMaterial(std::string type, vec3 color) = 0;
     virtual std::shared_ptr<material> getMaterial() = 0;
     virtual void setProperties(
         std::map<std::string, std::string> properties) = 0;
};

class hittable_list : public hittable {
    public:
        hittable_list() {}
        hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;
    void setPos(vec3 pos) override;
    vec3 getPos() override;
    void setMaterial(std::string type, vec3 color) override;
    std::shared_ptr<material> getMaterial() override;
    void setProperties(std::map<std::string, std::string> properties) override;

   public:
    std::vector<std::shared_ptr<hittable> > objects;
};
inline bool hittable_list::hit(const ray& r, double t_min, double t_max,
                               hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

inline void hittable_list::setPos(vec3 pos) {
    for (auto& object : objects) object->setPos(pos);
}

inline vec3 hittable_list::getPos() { return objects[0]->getPos(); }

inline void hittable_list::setMaterial(std::string type, vec3 color) {
    for (auto& object : objects) object->setMaterial(type, color);
}

inline std::shared_ptr<material> hittable_list::getMaterial() {
    return objects[0]->getMaterial();
}

inline void hittable_list::setProperties(
    std::map<std::string, std::string> properties) {
    for (auto& object : objects) object->setProperties(properties);
}
