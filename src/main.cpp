/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** main
*/

#include "Director.hpp"

bool check_args(int ac)
{
    if (ac < 3)
        return false;
    return true;
}

int main(int ac, char **av)
{
    if (!check_args(ac))
        return 84;
    try {
        std::string filename = av[1];
        Director director(filename, std::stoi(av[3]), av[2]);
        director.initThreads();
        director.joinThreads();
    } catch (ParserException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}