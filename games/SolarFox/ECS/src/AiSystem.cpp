/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#include "../include/AiSystem.hpp"

AISystem::AISystem()
= default;

AISystem::~AISystem()
= default;

void AISystem::update(Storage<AI> *AIStorage,
    Storage<Velocity> *velocityStorage
) const
{
    for (auto it : AIStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first)) {
            process(AIStorage, velocityStorage, it.first);
        }
    }
}

void AISystem::process(Storage<AI> *AIStorage,
    Storage<Velocity> *velocityStorage, unsigned long long int entityID
) const
{
    AIStorage->getComponentForEntity(entityID).randomAction = std::rand()%500;
    switch (AIStorage->getComponentForEntity(entityID).randomAction) {
    case 0:
        velocityStorage->getComponentForEntity(entityID).yOffset = 0;
        velocityStorage->getComponentForEntity(entityID).xOffset = (-1);
        break;
    case 1:
        velocityStorage->getComponentForEntity(entityID).yOffset = 0;
        velocityStorage->getComponentForEntity(entityID).xOffset = 1;
        break;
    case 2:
        velocityStorage->getComponentForEntity(entityID).xOffset = 0;
        velocityStorage->getComponentForEntity(entityID).yOffset = (-1);
        break;
    case 3:
        velocityStorage->getComponentForEntity(entityID).xOffset = 0;
        velocityStorage->getComponentForEntity(entityID).yOffset = 1;
        break;
    default:
        break;
    }
}
