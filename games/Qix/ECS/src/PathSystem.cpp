/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/PathSystem.hpp"


void PathSystem::update(Storage<Path> *pathStorage, Storage<Position> *positionStorage, Storage<Tag> *typeStorage) const
{
    for (auto it : pathStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->hasEntityComponent(it.first) && pathStorage->getComponentForEntity(it.first).canMakePath) {
            process(pathStorage, positionStorage, typeStorage, it.first);
        }
    }
}


void PathSystem::process(Storage<Path> *pathStorage,Storage<Position> *positionStorage, Storage<Tag> *typeStorage, unsigned long long int entityID) const
{
    for (auto it: positionStorage->entityIdxToComponentIdxMap) {
        if (it.first != entityID && positionStorage->getComponentForEntity(entityID).x == positionStorage->getComponentForEntity(it.first).x &&
            positionStorage->getComponentForEntity(entityID).y == positionStorage->getComponentForEntity(it.first).y) {
            typeStorage->getComponentForEntity(it.first).type = WALL_2;
            if (pathStorage->getComponentForEntity(entityID).path.rbegin()->first != positionStorage->getComponentForEntity(entityID).x ||
                pathStorage->getComponentForEntity(entityID).path.rbegin()->second != positionStorage->getComponentForEntity(entityID).y
            ) {
                pathStorage->getComponentForEntity(entityID).path.emplace_back(
                    positionStorage->getComponentForEntity(entityID).x,
                    positionStorage->getComponentForEntity(entityID).y);
            }
            break;
        }
    }
}