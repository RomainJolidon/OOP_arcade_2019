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
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Shooting> *shootingStorage,
    Storage<Tag> *typeStorage, Storage<Clock> *clockStorage, Storage<Follower> *followerStorage, Storage<Damage> *dmgStorage,
    Storage<Walkable> *walkableStorage
) const
{
    bool shooted = false;
    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first) && positionStorage->hasEntityComponent(it.first)) {
            bool tmp = process(
                positionStorage,
                velocityStorage,
                colliderStorage,
                shootingStorage,
                typeStorage,
                clockStorage,
                followerStorage,
                dmgStorage,
                walkableStorage,
            it.first);
            if (tmp)
                shooted = true;
        }
    }
    return shooted;
}

bool CollisionSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Collider> *colliderStorage, Storage<Shooting> *shootingStorage,
    Storage<Tag> *typeStorage, Storage<Clock> *clockStorage, Storage<Follower> *followerStorage, Storage<Damage> *dmgStorage,
    Storage<Walkable> *walkableStorage, unsigned long long int entityID
) const
{
    Position *entityPosition = &positionStorage->getComponentForEntity(entityID);
    Velocity *entityVelocity;
    Collider *entityCollider = &colliderStorage->getComponentForEntity(entityID);
    bool shooted = false;

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
            if (typeStorage->getComponentForEntity(it.first).type == WALL_1 && typeStorage->getComponentForEntity(entityID).type == ENEMY_1) {
                velocityStorage->getComponentForEntity(entityID).xOffset = -velocityStorage->getComponentForEntity(entityID).xOffset;
                positionStorage->getComponentForEntity(entityID).y++;
                continue;
            }
            if (shootingStorage->hasEntityComponent(entityID)) {
                if (typeStorage->getComponentForEntity(it.first).type == WALL_1) {
                    clockStorage->removeComponentForEntity(entityID);
                    typeStorage->removeComponentForEntity(entityID);
                    positionStorage->removeComponentForEntity(entityID);
                    velocityStorage->removeComponentForEntity(entityID);
                    shootingStorage->removeComponentForEntity(entityID);
                    if (dmgStorage->hasEntityComponent(it.first)) {    
                        dmgStorage->getComponentForEntity(it.first).health--;
                        if (dmgStorage->getComponentForEntity(it.first).health == 0) {
                            dmgStorage->removeComponentForEntity(it.first);
                            typeStorage->getComponentForEntity(it.first).type = FLOOR;
                            walkableStorage->addComponentForEntity(it.first);
                            walkableStorage->getComponentForEntity(it.first) = Walkable{it.first, 1, 1};
                        }
                    }
                }
                if (typeStorage->getComponentForEntity(it.first).type == shootingStorage->getComponentForEntity(entityID).target) {
                    shooted = true;
                    typeStorage->getComponentForEntity(it.first).type = WALL_1;
                    dmgStorage->addComponentForEntity(it.first);
                    dmgStorage->getComponentForEntity(it.first) = Damage{it.first, 5};
                    velocityStorage->removeComponentForEntity(it.first);
                    if (followerStorage->hasEntityComponent(it.first))
                        followerStorage->removeComponentForEntity(it.first);
                    for (auto &fol: followerStorage->componentVector) {
                        if (fol.targetId == it.first) {
                            clockStorage->addComponentForEntity(fol.entityId);
                            clockStorage->getComponentForEntity(fol.entityId) = Clock{fol.entityId, 0, 6};
                            followerStorage->removeComponentForEntity(fol.entityId);
                            velocityStorage->getComponentForEntity(fol.entityId) = Velocity{fol.entityId,
                                positionStorage->getComponentForEntity(it.first).x > positionStorage->getComponentForEntity(fol.entityId).x ? 1 : -1,
                            0};
                            process(positionStorage, velocityStorage, colliderStorage, shootingStorage, typeStorage, clockStorage, followerStorage, dmgStorage, walkableStorage, fol.entityId);
                        }
                    }
                }
            } else {
                velocityStorage->getComponentForEntity(entityID) = Velocity{entityID, 0, 0};
            }
        }
    }
    return shooted;
}

