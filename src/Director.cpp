/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** Director
*/

#include "Director.hpp"

inline void first_thread(std::shared_ptr<MainScene>& scene, sf::Image& image, std::vector<std::vector<vec3>>& colors, int& sample, int& max, bool& stopThreads)
{
    const int block_size = 25;
    const int width = scene->getWidth();
    const int height = scene->getHeight();
    while (true) {
        if (stopThreads)
            break;
        int start_x = -1, start_y = -1, end_x = -1, end_y = -1;
        for (int i = 0; i < width && start_x == -1; i += block_size) {
            for (int j = 0; j < height && start_x == -1; j += block_size) {
                if (colors[i][j].x() == -1) {
                    start_x = i;
                    start_y = j;
                    end_x = std::min(i + block_size, width);
                    end_y = std::min(j + block_size, height);
                }
            }
        }
        for (int y = start_y; y < end_y; ++y) {
            for (int x = start_x; x < end_x; ++x) {
                vec3 pixel_color(0, 0, 0);
                for (int s = 0; s < sample; ++s) {
                    float u = float(x + random_double()) / float(width);
                    float v = float(y + random_double()) / float(height);
                    ray r = scene->getCamera()->get_ray(u, v);
                    pixel_color += utils::ray_color(r, scene->getWorld(), max);
                }
                colors[x][y] = pixel_color / float(sample);
                image.setPixel(x, height - 1 - y, sf::Color(colors[x][y].x() * 255, colors[x][y].y() * 255, colors[x][y].z() * 255));
            }
        }
    }
}

Director::Director(std::string file, int thread, std::string _filename)
{
    _scene = std::make_shared<MainScene>();
    _nbthread = thread;
    _libhandler = std::make_unique<RaytracerCore::Libhandler>();
    _mainWindow = _libhandler->loadAndGetlib<ISfml>("./sfmlhandler.so", "SFML");
    // _info = _libhandler->loadAndGetlib<ISfml>("./sfmlhandler.so", "SFML");
    _mainWindow->setWindowsize(1920,1080);
    _threads.resize(_nbthread);
    _scene->initparser(file);
    _file = _filename;
    _scene->initcamera();
    _scene->initprimitives();
    _needchange = false;
    _savecolors.resize(
        _scene->getWidth(),
        std::vector<vec3>(_scene->getHeight(), vec3(-1, -1, -1)));
    for (auto& savecolors : _savecolors) {
        for (auto& color : savecolors) {
            color = vec3(-1, -1, -1);
        }
    }
}

Director::~Director()
{
    _threads.clear();
    for (auto savecolors : _savecolors)
        savecolors.clear();
    _savecolors.clear();
}

void Director::initThreads()
{
    _scene->setImage(_scene->getWidth(), _scene->getHeight());
    // _drawer = std::thread(&Director::DrawWindow, this);
}

void Director::stopThreads()
{
    for (auto& thread : _threads) {
        if (thread.joinable()) thread.join();
    }
}

void Director::joinThreads()
{
    for (int i = 0; i < _nbthread; ++i) {
        _threads[i] = std::thread(
            first_thread, std::ref(_scene), std::ref(_scene->getImage()),
            std::ref(_savecolors), std::ref(sample), std::ref(max),
            std::ref(_stopThreads));
    }
    for (int i = 0; i < _nbthread; ++i) {
        _threads[i].detach();
    }
    DrawWindow();
}
