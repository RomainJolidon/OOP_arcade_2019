/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include <zconf.h>
#include "../include/MovementSystem.hpp"

MovementSystem::MovementSystem()
= default;

MovementSystem::~MovementSystem()
= default;

void MovementSystem::update(Storage<Position> *positionStorage, Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, Storage<Tag> *typeStorage, FollowerSystem *_follow, Storage<Follower> *followerStorage) const
{
    for (auto it : clockStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->hasEntityComponent(it.first) && velocityStorage->hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, clockStorage, typeStorage, _follow, followerStorage, it.first);
        }
    }
}

void MovementSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, Storage<Tag> *typeStorage, FollowerSystem *_follow, Storage<Follower> *followerStorage, unsigned long long int entityID) const
{
    if (clockStorage->getComponentForEntity(entityID).tickCount >= clockStorage->getComponentForEntity(entityID).limit) {
        if (velocityStorage->getComponentForEntity(entityID).xOffset == 0 && velocityStorage->getComponentForEntity(entityID).yOffset == 0)
            return;
        positionStorage->getComponentForEntity(entityID).x += velocityStorage->getComponentForEntity(entityID).xOffset;
        positionStorage->getComponentForEntity(entityID).y += velocityStorage->getComponentForEntity(entityID).yOffset;
        clockStorage->getComponentForEntity(entityID).tickCount = 0;
        if (followerStorage->hasEntityComponent(entityID) == false && typeStorage->getComponentForEntity(entityID).type == ENEMY_1)
            _follow->update(followerStorage, velocityStorage, positionStorage, entityID);
    }
}