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

void CollisionSystem::update(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Follower> *followerStorage
) const
{
    for (auto it : colliderStorage->componentVector) {
        if (velocityStorage->hasEntityComponent(it.entityId) && positionStorage->hasEntityComponent(it.entityId)) {
            process(positionStorage, velocityStorage, colliderStorage, followerStorage, it.entityId);
        }
    }
}

void CollisionSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Follower> *followerStorage,
    unsigned long long int entityID
) const
{
    if (velocityStorage->getComponentForEntity(entityID).xOffset == 0 && velocityStorage->getComponentForEntity(entityID).yOffset == 0)
        return;
    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (it.first != entityID &&
        positionStorage->getComponentForEntity(entityID).x + velocityStorage->getComponentForEntity(entityID).xOffset ==
        positionStorage->getComponentForEntity(it.first).x + velocityStorage->getComponentForEntity(it.first).xOffset &&
        positionStorage->getComponentForEntity(entityID).y + velocityStorage->getComponentForEntity(entityID).yOffset ==
        positionStorage->getComponentForEntity(it.first).y + velocityStorage->getComponentForEntity(it.first).yOffset
        ) {
            if (followerStorage->hasEntityComponent(it.first) &&
                (followerStorage->getComponentForEntity(it.first).xSave != velocityStorage->getComponentForEntity(it.first).xOffset ||
                followerStorage->getComponentForEntity(it.first).ySave != velocityStorage->getComponentForEntity(it.first).yOffset)
                ) {
                return;
            } else if (followerStorage->hasEntityComponent(entityID) &&
                (followerStorage->getComponentForEntity(entityID).xSave != velocityStorage->getComponentForEntity(entityID).xOffset ||
                    followerStorage->getComponentForEntity(entityID).ySave != velocityStorage->getComponentForEntity(entityID).yOffset)
                ) {
                return;
            }
            velocityStorage->getComponentForEntity(entityID) = Velocity{entityID, 0, 0};
            velocityStorage->getComponentForEntity(it.first) = Velocity{it.first, 0, 0};
        }
    }
}

