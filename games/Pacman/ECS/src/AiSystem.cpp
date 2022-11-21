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
    Velocity *entityVelocity = &velocityStorage->getComponentForEntity(entityID);
    AI *entityAI = &AIStorage->getComponentForEntity(entityID);

    entityAI->randomAction = std::rand()%6;
    switch (entityAI->randomAction) {
    case 0:
        entityVelocity->yOffset = 0;
        entityVelocity->xOffset = (-1);
        break;
    case 1:
        entityVelocity->yOffset = 0;
        entityVelocity->xOffset = 1;
        break;
    case 2:
        entityVelocity->xOffset = 0;
        entityVelocity->yOffset = (-1);
        break;
    case 3:
        entityVelocity->xOffset = 0;
        entityVelocity->yOffset = 1;
        break;
    default:
        break;
    }
}
