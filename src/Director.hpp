/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-flavien.maameri
** File description:
** Director
*/

#include "scene.hpp"
#include <thread>
#include <future>
#include "Libhandler.hpp"
#include "Input.hpp"

class Director {
    public:
        Director(std::string file, int nbthread, std::string _filename);
        ~Director();
        void initThreads();
        void joinThreads();
        void DrawWindow();
        void handleEvents(std::vector<Input> Inputs);
        void stopThreads();
    private:
        std::vector<std::thread> _threads;
        std::thread _finalRender;
        std::shared_ptr<MainScene> _scene;
        std::vector<std::vector<vec3>> _savecolors;
        int _nbthread;
        std::thread _drawer;
        bool _needchange = false;
        bool _renderedfinal = false;
        sf::Image _lastimage;
        std::mutex _mutex;
        std::condition_variable _cv;
        bool _stopThreads = false;
        std::string _file;
        int sample = 1;
        int max = 1;
        std::shared_ptr<ISfml> _mainWindow;
        std::unique_ptr<RaytracerCore::Libhandler> _libhandler;
};