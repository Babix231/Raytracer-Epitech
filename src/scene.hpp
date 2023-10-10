/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** scene
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "camera.hpp"
#include "hitable.hpp"
#include "parser.hpp"
#include "factory.hpp"
#include <SFML/Graphics.hpp>

class MainScene {
    public:
     MainScene() { _factory = Factory();}
     ~MainScene(){};
     void initparser(std::string file);
     void initcamera();
     void initprimitives();
     void setcameraPos(vec3 pos) {
        _camera->setPos(pos);
        };
     std::vector<std::shared_ptr<hittable>> &getPrimitives() {
         return _primitives;
     };
     int getWidth() { return _width; };
     void setWidth(int width) { _width = width; };
     int getHeight() { return _height; };
     void setHeight(int height) { _height = height; };
     void setImage(int width, int height) { _image.create(width, height); };
     sf::Image &getImage() { return _image; };
     inline std::unique_ptr<camera> &getCamera() { return _camera; };
     hittable_list &getWorld() { return _world; };
    private:
        std::unique_ptr<parser> _parser;
        std::unique_ptr<camera> _camera;
        std::vector<std::shared_ptr<hittable>> _primitives;
        Factory _factory;
        sf::Image _image;
        int _width;
        int _height;
        hittable_list _world;
};
