/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/FollowerSystem.hpp"

FollowerSystem::FollowerSystem()
{
}

FollowerSystem::~FollowerSystem()
{
}

void FollowerSystem::update(Storage<Follower> *FollowerStorage,
    Storage<Velocity> *velocityStorage
) const
{
    for (auto it : FollowerStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first)) {
            process(FollowerStorage, velocityStorage, it.first);
        }
    }
}

void FollowerSystem::process(Storage<Follower> *followerStorage,
    Storage<Velocity> *velocityStorage, unsigned long long int entityID
) const
{
    std::cout << "on arrive dans le process de follower" << std::endl;
    unsigned long long int targetId = followerStorage->getComponentForEntity(entityID).targetId;
    int x = velocityStorage->getComponentForEntity(targetId).xOffset;
    int y = velocityStorage->getComponentForEntity(targetId).yOffset;

    //std::cout << "x: " << x << ", y: " << y << std::endl;
    velocityStorage->getComponentForEntity(entityID).xOffset = x;
    velocityStorage->getComponentForEntity(entityID).yOffset = y;
    //std::cout << "x: " << velocityStorage->getComponentForEntity(entityID).xOffset << ", y: " << velocityStorage->getComponentForEntity(entityID).yOffset << std::endl;
    std::cout << "follower id: " << entityID << std::endl;
}
