/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** factory
*/

#pragma once

#include "hitable.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "cylinder.hpp"
#include <unordered_map>
#include <functional>
#include "cube.hpp"
#include "triangle.hpp"
#include <memory>
#include "material.hpp"
#include "objfile.hpp"
class Factory
{

   public:
    Factory() {
        primitives_factories["sphere"] = []() { return std::make_shared<RaytracerPrimitives::sphere>(); };
        primitives_factories["plane"] = []() { return std::make_shared<RaytracerPrimitives::plane>(); };
        primitives_factories["cylindre"] = []() { return std::make_shared<RaytracerPrimitives::cylindre>(); };
        primitives_factories["cube"] = []() { return std::make_shared<RaytracerPrimitives::cube>(); };
        primitives_factories["triangle"] = []() { return std::make_shared<RaytracerPrimitives::Triangle>(); };
        primitives_factories["objfile"] = []() { return std::make_shared<RaytracerPrimitives::Objfile>(); };
    }

    ~Factory() {
        primitives_factories.clear();
    }
    std::shared_ptr<hittable> createPrimitives(const std::string &type) {
        if (primitives_factories.find(type) == primitives_factories.end())
            exit(0);
        return primitives_factories.at(type)();
    }
   private:
    std::unordered_map<std::string, std::function<std::shared_ptr<hittable>()>>
        primitives_factories;
};
