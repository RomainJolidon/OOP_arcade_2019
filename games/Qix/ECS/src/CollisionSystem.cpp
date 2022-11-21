/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "../include/CollisionSystem.hpp"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::update(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Tag> *typeStorage
) const
{
    for (auto it : colliderStorage->componentVector) {
        if (velocityStorage->hasEntityComponent(it.entityId) && positionStorage->hasEntityComponent(it.entityId)) {
            if (!process(positionStorage, velocityStorage, typeStorage, it.entityId))
                return (false);
        }
    }
    return (true);
}

bool CollisionSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Tag> *typeStorage, unsigned long long int entityID
) const
{
    int x = positionStorage->getComponentForEntity(entityID).x + velocityStorage->getComponentForEntity(entityID).xOffset;
    int y = positionStorage->getComponentForEntity(entityID).y + velocityStorage->getComponentForEntity(entityID).yOffset;

    for (auto it : positionStorage->entityIdxToComponentIdxMap) {
        if (it.first != entityID && positionStorage->getComponentForEntity(it.first).x == x &&
        positionStorage->getComponentForEntity(it.first).y == y) {

            return !(
                typeStorage->getComponentForEntity(it.first).type == ENEMY_1 &&
                    typeStorage->getComponentForEntity(entityID).type ==
                        PLAYER_1);
        }
    }
    velocityStorage->getComponentForEntity(entityID).xOffset = 0;
    velocityStorage->getComponentForEntity(entityID).yOffset = 0;
    return (true);
}

