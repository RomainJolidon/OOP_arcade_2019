/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_PATHSYSTEM_HPP
#define OOP_ARCADE_2019_PATHSYSTEM_HPP

#include "Storage.hpp"

class PathSystem {
    public:
    PathSystem() = default;
    ~PathSystem() = default;
    void update(Storage<Path> *pathStorage, Storage<Position> *positionStorage, Storage<Tag> *typeStorage) const;

    protected:
    private:
    void process(Storage<Path> *pathStorage,Storage<Position> *positionStorage, Storage<Tag> *typeStorage, unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_PATHSYSTEM_HPP
