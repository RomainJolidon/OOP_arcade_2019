/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/FollowerSystem.hpp"

FollowerSystem::FollowerSystem()
: _authorized(true)
{
}

FollowerSystem::~FollowerSystem()
{
}

void FollowerSystem::update(Storage<Follower> *FollowerStorage,
    Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, unsigned long long int headID
)
{
    bool modified;
    unsigned long long int currentTarget = headID;

    do {
        modified = false;
        for (auto it: FollowerStorage->componentVector) {
            if (it.targetId == currentTarget) {
                modified = true;
                process(FollowerStorage, velocityStorage, positionStorage, it.entityId);
                currentTarget = it.entityId;
            }
        }
    } while (modified);
    _authorized = false;
}

void FollowerSystem::process(Storage<Follower> *followerStorage,
    Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, unsigned long long int entityID
) const
{
    unsigned long long int targetId = followerStorage->getComponentForEntity(entityID).targetId;
    int x = velocityStorage->getComponentForEntity(targetId).xOffset;
    int y = velocityStorage->getComponentForEntity(targetId).yOffset;

    velocityStorage->getComponentForEntity(entityID).xOffset = followerStorage->getComponentForEntity(entityID).xSave;
    velocityStorage->getComponentForEntity(entityID).yOffset = followerStorage->getComponentForEntity(entityID).ySave;
    if ((x != 0 || y != 0)) {
        followerStorage->getComponentForEntity(entityID).xSave = x;
        followerStorage->getComponentForEntity(entityID).ySave = y;
    }
    positionStorage->getComponentForEntity(entityID).x += velocityStorage->getComponentForEntity(entityID).xOffset;
    positionStorage->getComponentForEntity(entityID).y += velocityStorage->getComponentForEntity(entityID).yOffset;
}

void FollowerSystem::authorize()
{
    _authorized = true;
}
