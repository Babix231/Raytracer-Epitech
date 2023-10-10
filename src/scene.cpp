/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** scene
*/

#include "scene.hpp"
#include "objfile.hpp"
#include "triangle.hpp"
#include <list>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<RaytracerPrimitives::Triangle> parserObjfile(std::string filename)
{
    std::ifstream objfile(filename);
    std::string line;
    std::vector<vec3> vertices;
    std::vector<RaytracerPrimitives::Triangle> triangles;
    while (std::getline(objfile, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;
        if (keyword == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        } else if (keyword == "f") {
            int v1, v2, v3;
            iss >> v1 >> v2 >> v3;
            triangles.emplace_back(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1]);
        }
    }
    return triangles;
}

void MainScene::initparser(std::string file)
{
    _parser = std::make_unique<parser>(file);
    _parser->execute();
}

void MainScene::initcamera()
{
    CameraSettings settings = _parser->getCameraConfig();
    vec3 position = {settings.position.x, settings.position.y, settings.position.z};
    vec3 rotation = {settings.rotation.x, settings.rotation.y, settings.rotation.z};
    _width = settings.width;
    _height = settings.height;
    _camera = std::make_unique<camera>(settings.width,settings.height,position, rotation, vec3(0, 1, 0), settings.fov);
}

void MainScene::initprimitives()
{
    std::vector<Settings> primitives = _parser->getPrimitives();
    for (auto& my : primitives) {
        if (my.type == "objfile") {
            auto objprimitive = std::make_shared<RaytracerPrimitives::Objfile>();
            std::vector<RaytracerPrimitives::Triangle> triangles = parserObjfile(my.properties["path"]);
            for (auto& triangle : triangles) {
                triangle.setMaterial(my.material, my.color);
                triangle.setProperties(my.properties);
                triangle.setPos(my.position);
            }
            objprimitive->setTriangles(triangles);
            _world.add(objprimitive);
        } else {
            _primitives.push_back(_factory.createPrimitives(my.type));
            _primitives.back()->setPos(my.position);
            _primitives.back()->setMaterial(my.material, my.color);
            _primitives.back()->setProperties(my.properties);
            _world.add(_primitives.back());
        }
    }
}
