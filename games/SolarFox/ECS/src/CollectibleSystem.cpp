/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/CollectibleSystem.hpp"

CollectibleSystem::CollectibleSystem()
{
}

CollectibleSystem::~CollectibleSystem()
{
}

bool CollectibleSystem::update(Storage<Collectible> *collectibleStorage, Storage<Tag> *typeStorage, Storage<Position> *positionStorage,
    Storage<Playable> *playerStorage)
{
    for (auto & it : playerStorage->entityIdxToComponentIdxMap) {
            if (process(collectibleStorage, typeStorage, positionStorage, it.first))
                return (true);
    }
    return (false);
}

bool CollectibleSystem::process(Storage<Collectible> *collectibleStorage, Storage<Tag> *typeStorage, Storage<Position> *positionStorage, unsigned long long int entityID) const
{
    int x = positionStorage->getComponentForEntity(entityID).x;
    int y = positionStorage->getComponentForEntity(entityID).y;

    for (auto & it: collectibleStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->getComponentForEntity(it.first).x == x && positionStorage->getComponentForEntity(it.first).y == y) {
            typeStorage->getComponentForEntity(it.first).type = FLOOR;
            collectibleStorage->removeComponentForEntity(it.first);
            return (true);
        }
    }
    return (false);
}