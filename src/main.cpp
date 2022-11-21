/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "Core.hpp"

int main(int ac, char **av)
{
    std::string libName;
    Core core;

    if (!Parser::checkArgs(ac, av))
        return (84);
    libName = av[1];
    try {
        core.StartCoreMenu(libName);
    } catch (const Error::ArcadeError& e) {
        std::cout << e.what() << std::endl;
        return (84);
    }
    return (0);
}