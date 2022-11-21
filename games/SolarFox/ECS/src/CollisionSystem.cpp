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
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Shooting> *shootingStorage,
    Storage<Tag> *typeStorage, Storage<Clock> *clockStorage
) const
{
    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first) && positionStorage->hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, colliderStorage, shootingStorage, typeStorage, clockStorage, it.first);
        }
    }
}

void CollisionSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Shooting> *shootingStorage,
    Storage<Tag> *typeStorage, Storage<Clock> *clockStorage, unsigned long long int entityID
) const
{
    Position *entityPosition = &positionStorage->getComponentForEntity(entityID);
    Velocity *entityVelocity;
    Collider *entityCollider = &colliderStorage->getComponentForEntity(entityID);

    Position *otherEntityPosition;
    Collider *otherEntityCollider;
    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (it.first == entityID || !velocityStorage->hasEntityComponent(entityID) || (velocityStorage->getComponentForEntity(entityID).xOffset == 0 && velocityStorage->getComponentForEntity(entityID).yOffset == 0))
            continue;
        entityVelocity = &velocityStorage->getComponentForEntity(entityID);
        otherEntityPosition = &positionStorage->getComponentForEntity(it.first);
        otherEntityCollider = &colliderStorage->getComponentForEntity(it.first);
        if (entityPosition->x + entityVelocity->xOffset < otherEntityPosition->x + otherEntityCollider->width &&
            entityPosition->x + entityVelocity->xOffset + entityCollider->width > otherEntityPosition->x &&
            entityPosition->y + entityVelocity->yOffset < otherEntityPosition->y + otherEntityCollider->height &&
            entityPosition->y + entityVelocity->yOffset + entityCollider->height > otherEntityPosition->y)
        {
            if (shootingStorage->hasEntityComponent(entityID)) {
                if (typeStorage->getComponentForEntity(it.first).type == shootingStorage->getComponentForEntity(entityID).target) {
                    clockStorage->removeComponentForEntity(it.first);
                    typeStorage->removeComponentForEntity(it.first);
                    positionStorage->removeComponentForEntity(it.first);
                    velocityStorage->removeComponentForEntity(it.first);
                    if (shootingStorage->hasEntityComponent(it.first)) {
                        shootingStorage->removeComponentForEntity(it.first);
                    }
                }
            } else {
                velocityStorage->getComponentForEntity(entityID) = Velocity{entityID, 0, 0};
            }
            velocityStorage->getComponentForEntity(it.first) = Velocity{it.first, 0, 0};
        }
    }
}

