/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** DirectorSFML
*/

#include "Director.hpp"

static void clearVector(std::vector<std::vector<vec3>> &savecolors)
{
    for (auto &savecolor : savecolors) {
        for (auto &color : savecolor) {
            color = vec3(-1, -1, -1);
        }
    }
}

inline void Director::handleEvents(std::vector<Input> Inputs)
{
    for (auto event : Inputs) {
        if (event == Input::ESCAPE) {
            std::exit(0);
        }
        if (event == Input::Z_KEY) {
            _scene->setcameraPos(_scene->getCamera()->getPos() + vec3(0, 0, -2));
            clearVector(_savecolors);
        }
        if (event == Input::S_KEY) {
            _scene->setcameraPos(_scene->getCamera()->getPos() + vec3(0, 0, 2));
            clearVector(_savecolors);
        }
        if (event == Input::Q_KEY) {
            _scene->setcameraPos(_scene->getCamera()->getPos() + vec3(-2, 0, 0));
            clearVector(_savecolors);
        }
        if (event == Input::D_KEY) {
            _scene->setcameraPos(_scene->getCamera()->getPos() + vec3(2, 0, 0));
            clearVector(_savecolors);
        }
        if (event == Input::UP_ARROW) {
            _scene->setcameraPos(_scene->getCamera()->getPos() + vec3(0, 2, 0));
            clearVector(_savecolors);
        }
        if (event == Input::DOWN_ARROW) {
            _scene->setcameraPos(_scene->getCamera()->getPos() + vec3(0, -2, 0));
            clearVector(_savecolors);
        }
        if (event == Input::ENTER) {
            std::cout << "camera pos : " << _scene->getCamera()->getPos()
                      << std::endl;
            if (_file.find(".png") != std::string::npos)
                _scene->getImage().saveToFile(_file);
            else
                _scene->getImage().saveToFile("default.png");
        }
        if (event == Input::RIGHT_ARROW) {
            sample = 100;
            max = 100;
            clearVector(_savecolors);
        }
        if (event == Input::LEFT_ARROW) {
            sample = 4;
            max = 4;
            clearVector(_savecolors);
        }
    }
}

void Director::DrawWindow()
{
    while (1) {
        _mainWindow->drawImage(_scene->getImage());
        _mainWindow->refreshGraph();
        _mainWindow->checkEvent();
        handleEvents(_mainWindow->getInputs());
    }
}
