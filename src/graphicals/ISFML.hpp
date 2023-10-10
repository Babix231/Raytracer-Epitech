/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** ISFML
*/

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../Input.hpp"

class ISfml {
    public:
        virtual ~ISfml() = default;
        // virtual void drawText(const std::string &text, int x, int y,MyColor cl) = 0;
        virtual void refreshGraph() = 0;
        virtual void checkEvent() = 0;
        virtual std::vector<Input> getInputs() = 0;
        virtual void drawImage(sf::Image &image) = 0;
        // virtual void setColor(std::map<char, std::tuple<std::string, MyColor>>) = 0;
        virtual void setWindowsize(int x , int y) = 0;
       protected:
       private:
};

class HandlerSFML : public ISfml {
    public:
        HandlerSFML();
        ~HandlerSFML() override;
        void refreshGraph() override;
        void drawImage(sf::Image &image) override;
        void setWindowsize(int x, int y) override;
        void checkEvent() override;
        std::vector<Input> getInputs() override { return _inputV; };

       protected:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Image _image;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Font _font;
        int scalex = 1;
        std::vector<Input> _inputV;
        int scaley = 1;
        std::vector<sf::Text> _text;
        bool buttoninit = false;
        // std::map<char, std::tuple<std::string, MyColor>> _color;
    private:
};