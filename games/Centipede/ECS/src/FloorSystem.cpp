/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#include "../include/FloorSystem.hpp"

FloorSystem::FloorSystem()
{
}

FloorSystem::~FloorSystem()
{
}

void FloorSystem::update(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage,
    Storage<Walkable> *walkableStorage, Storage<Shooting> *shootingStorage
) const
{
    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first) && positionStorage->hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, colliderStorage, walkableStorage, shootingStorage, it.first);
        }
    }
}

void FloorSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage,
    Storage<Walkable> *walkableStorage, Storage<Shooting> *shootingStorage,
    unsigned long long int entityID
) const
{
    bool isAbleToWalk = false;
    for (auto it : walkableStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->getComponentForEntity(entityID).x +
            velocityStorage->getComponentForEntity(entityID).xOffset <
            positionStorage->getComponentForEntity(it.first).x +
            walkableStorage->getComponentForEntity(it.first).width &&
            positionStorage->getComponentForEntity(entityID).x +
            velocityStorage->getComponentForEntity(entityID).xOffset +
            colliderStorage->getComponentForEntity(entityID).width >
            positionStorage->getComponentForEntity(it.first).x &&

            positionStorage->getComponentForEntity(entityID).y +
            velocityStorage->getComponentForEntity(entityID).yOffset <
            positionStorage->getComponentForEntity(it.first).y +
            walkableStorage->getComponentForEntity(it.first).height &&
            positionStorage->getComponentForEntity(entityID).y +
            velocityStorage->getComponentForEntity(entityID).yOffset +
            colliderStorage->getComponentForEntity(entityID).height >
            positionStorage->getComponentForEntity(it.first).y)
            isAbleToWalk = true;
    }
    if (shootingStorage->hasEntityComponent(entityID))
        isAbleToWalk = true;
    if (!isAbleToWalk)
        velocityStorage->getComponentForEntity(entityID) = Velocity{entityID, 0, 0};
}
