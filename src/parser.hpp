/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** parser
*/

#pragma once
// #include "/opt/homebrew/Cellar/libconfig/1.7.3/include/libconfig.h++"
#include <libconfig.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <map>
#include "vec3.hpp"

struct CameraSettings {
    double fov;
    int width;
    int height;
    struct {
        double x;
        double y;
        double z;
    } position;
    struct {
        double x;
        double y;
        double z;
    } rotation;
};

struct Settings {
    vec3 position;
    vec3 color;
    std::string material;
    std::string type;
    std::map<std::string, std::string> properties;
};

class ParserException : public std::exception
{
    public:
        ParserException() : _message("Error: Unknown") {};
        ParserException(std::string message) : _message(message) {};
        ~ParserException() {};
        const char *what() const noexcept { return _message.c_str(); };

    protected:
    private:
        std::string _message;
};

class parser : public ParserException
{
public:
    parser(std::string file) : _file(file) {};
    ~parser() {};
    void execute();
    CameraSettings getCameraConfig() const { return _cameraConfig; };
    std::vector<Settings> getPrimitives() const { return _hittable; };
private:
    std::string _file;
    std::vector<Settings> _hittable;
    CameraSettings _cameraConfig;
};
