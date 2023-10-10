/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** sfml
*/

#include "ISFML.hpp"

extern "C" HandlerSFML *createSFML() {
    return new HandlerSFML();
}

extern "C" void deleteSFML(HandlerSFML *ptr) {
    delete ptr;
}

HandlerSFML::HandlerSFML()
{
    _window.create(sf::VideoMode(1920, 1080), "Raytracer");
    _window.setFramerateLimit(60);
    // _font.loadFromFile("./arial_narrow_7.ttf");
}

HandlerSFML::~HandlerSFML()
{
    _window.close();
}

void HandlerSFML::refreshGraph()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
    for (size_t i = 0; i < _text.size(); i++) {
        _window.draw(_text[i]);
    }
    _window.display();
}

void HandlerSFML::drawImage(sf::Image &image)
{
    _image = image;
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);
    _sprite.setScale(float(_window.getSize().x) / float(_texture.getSize().x),
            float(_window.getSize().y) / float(_texture.getSize().y));
    _window.draw(_sprite);
}

void HandlerSFML::checkEvent()
{
    _inputV.clear();
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _inputV.push_back(Input::CLOSE);
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Up:
                        _inputV.push_back(Input::UP_ARROW);
                    break;
                case sf::Keyboard::Down:
                    _inputV.push_back(Input::DOWN_ARROW);
                    break;
                case sf::Keyboard::Left:
                    _inputV.push_back(Input::LEFT_ARROW);
                    break;
                case sf::Keyboard::Right:
                    _inputV.push_back(Input::RIGHT_ARROW);
                    break;
                case sf::Keyboard::Escape:
                    _inputV.push_back(Input::ESCAPE);
                    break;
                case sf::Keyboard::Return:
                    _inputV.push_back(Input::ENTER);
                    break;
                case sf::Keyboard::Space:
                    _inputV.push_back(Input::SPACE);
                    break;
                case sf::Keyboard::Num1:
                    _inputV.push_back(Input::KEY_1);
                    break;
                case sf::Keyboard::Num2:
                    _inputV.push_back(Input::KEY_2);
                    break;
                case sf::Keyboard::Num3:
                    _inputV.push_back(Input::KEY_3);
                    break;
                case sf::Keyboard::Num4:
                    _inputV.push_back(Input::KEY_4);
                    break;
                case sf::Keyboard::Num5:
                    _inputV.push_back(Input::KEY_5);
                    break;
                // ZQSD
                case sf::Keyboard::Z:
                    _inputV.push_back(Input::Z_KEY);
                    break;
                case sf::Keyboard::Q:
                    _inputV.push_back(Input::Q_KEY);
                    break;
                case sf::Keyboard::S:
                    _inputV.push_back(Input::S_KEY);
                    break;
                case sf::Keyboard::D:
                    _inputV.push_back(Input::D_KEY);
                    break;
                default:
                    _inputV.push_back(Input::NO_INPUT);
            }
        }
    }
    _inputV.push_back(Input::NO_INPUT);
}

void HandlerSFML::setWindowsize(int x , int y)
{
    _window.setSize(sf::Vector2u(x,y));
}
