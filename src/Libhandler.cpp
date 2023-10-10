/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-lefeuvre.aristide
** File description:
** Libhandler
*/

#include "Libhandler.hpp"

RaytracerCore::Libhandler::Libhandler()
{

}

RaytracerCore::Libhandler::~Libhandler()
{

}

void * RaytracerCore::Libhandler::loadLibrary(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw RaytracerCore::LibhandlerException("Cannot open library");
    }
    return handle;
}

void * RaytracerCore::Libhandler::loadFunction(void *handle, const std::string &name)
{
    void *func = dlsym(handle, name.c_str());
    if (!func) {
        throw RaytracerCore::LibhandlerException("Cannot load function");
    }
    return func;
}

void RaytracerCore::Libhandler::unloadLibrary(void *handle)
{
    dlclose(handle);
}