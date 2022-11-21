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

bool MovementSystem::update(Storage<Position> *positionStorage, Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage,
    FollowerSystem *_follow, Storage<Follower> *followerStorage) const
{
    for (auto it : clockStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->hasEntityComponent(it.first) && velocityStorage->hasEntityComponent(it.first)) {
            if (!process(positionStorage, velocityStorage, clockStorage, it.first, _follow, followerStorage))
                return (false);
        }
    }
    return (true);
}

bool MovementSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, unsigned long long int entityID, FollowerSystem *_follow, Storage<Follower> *followerStorage) const
{
    if (clockStorage->getComponentForEntity(entityID).tickCount >= clockStorage->getComponentForEntity(entityID).limit) {
        if (velocityStorage->getComponentForEntity(entityID).xOffset == 0 && velocityStorage->getComponentForEntity(entityID).yOffset == 0)
            return (false);
        positionStorage->getComponentForEntity(
            entityID).x += velocityStorage->getComponentForEntity(
            entityID).xOffset;
        positionStorage->getComponentForEntity(
            entityID).y += velocityStorage->getComponentForEntity(
            entityID).yOffset;
        clockStorage->getComponentForEntity(entityID).tickCount = 0;
        _follow->update(followerStorage, velocityStorage, positionStorage);
    }
    return (true);
}



