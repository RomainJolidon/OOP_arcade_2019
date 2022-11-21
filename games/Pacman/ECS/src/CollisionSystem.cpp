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

void CollisionSystem::update(
    Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage,
    Storage<Collider> *colliderStorage,
    Storage<Tag> *typeStorage,
    Storage<Playable> *playableStorage,
    Storage<Bonus> *bonusStorage
) const
{
    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, colliderStorage, typeStorage, playableStorage, bonusStorage, it.first);
            if (playableStorage->componentVector.empty())
                return;
        }
    }
}

void CollisionSystem::process(
    Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage,
    Storage<Collider> *colliderStorage,
    Storage<Tag> *typeStorage,
    Storage<Playable> *playableStorage,
    Storage<Bonus> *bonusStorage,
    unsigned long long int entityID
) const
{
    Position *entityPosition = &positionStorage->getComponentForEntity(entityID);
    Velocity *entityVelocity;
    Collider *entityCollider = &colliderStorage->getComponentForEntity(entityID);
    Tag *entityType = &typeStorage->getComponentForEntity(entityID);

    Position *otherEntityPosition;
    Collider *otherEntityCollider;
    Tag *otherEntityType;

    for (auto it : colliderStorage->entityIdxToComponentIdxMap) {
        if (it.first == entityID || !velocityStorage->hasEntityComponent(entityID) || (velocityStorage->getComponentForEntity(entityID).xOffset == 0 && velocityStorage->getComponentForEntity(entityID).yOffset == 0))
            continue;
        entityVelocity = &velocityStorage->getComponentForEntity(entityID);
        otherEntityPosition = &positionStorage->getComponentForEntity(it.first);
        otherEntityCollider = &colliderStorage->getComponentForEntity(it.first);
        otherEntityType = &typeStorage->getComponentForEntity(it.first);
        if ((entityType->type == PLAYER_1 && (otherEntityType->type == BONUS_1 || otherEntityType->type == BONUS_2 || otherEntityType->type == BONUS_3)) && ((entityPosition->x == otherEntityPosition->x) && (entityPosition->y == otherEntityPosition->y))) {
            playableStorage->getComponentForEntity(entityID).effect = bonusStorage->getComponentForEntity(it.first).effect;
            if (bonusStorage->getComponentForEntity(it.first).effect == BONUS1 || bonusStorage->getComponentForEntity(it.first).effect == SUPERBONUS1) {
                colliderStorage->removeComponentForEntity(it.first);
                typeStorage->getComponentForEntity(it.first).type = FLOOR;
                if (velocityStorage->hasEntityComponent(it.first))
                    velocityStorage->removeComponentForEntity(it.first);
                if (bonusStorage->hasEntityComponent(it.first))
                    bonusStorage->removeComponentForEntity(it.first);
            } else if (bonusStorage->getComponentForEntity(it.first).effect == SUPERBONUS2) {
                typeStorage->getComponentForEntity(it.first).type = ENEMY_1;
                if (bonusStorage->hasEntityComponent(it.first))
                    bonusStorage->removeComponentForEntity(it.first);
                positionStorage->getComponentForEntity(it.first).x = positionStorage->getComponentForEntity(it.first).initialPosX;
                positionStorage->getComponentForEntity(it.first).y = positionStorage->getComponentForEntity(it.first).initialPosY;
            }
            continue;
        } else if (entityPosition->x +
        entityVelocity->xOffset <
        otherEntityPosition->x +
        otherEntityCollider->width &&
        entityPosition->x +
        entityVelocity->xOffset +
        entityCollider->width >
        otherEntityPosition->x &&

        entityPosition->y +
        entityVelocity->yOffset <
        otherEntityPosition->y +
        otherEntityCollider->height &&
        entityPosition->y +
        entityVelocity->yOffset +
        entityCollider->height >
        otherEntityPosition->y) {
            if ((otherEntityType->type != BONUS_1 && otherEntityType->type != BONUS_2 && otherEntityType->type != BONUS_3) && otherEntityType->type != FLOOR)
                *entityVelocity = Velocity{entityID, 0, 0};
            if ((entityType->type == PLAYER_1 &&
                otherEntityType->type == ENEMY_1)) {
                playableStorage->removeComponentForEntity(entityID);
                return;
            }
            if ((entityType->type == ENEMY_1
            && otherEntityType->type == PLAYER_1)) {
                playableStorage->removeComponentForEntity(it.first);
                return;
            }
        }
    }
}

