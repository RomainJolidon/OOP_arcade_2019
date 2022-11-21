/*
** EPITECH PROJECT, 2023
** OOParcade2019
** File description:
** Created by jfournier,
*/

#include "../include/InputSystem.hpp"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update(Storage<Playable> *playableStorage,
    Storage<Velocity> *velocityStorage, KeyBind key
) const
{
    for (auto it : playableStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first)) {
            process(playableStorage, velocityStorage, it.first, key);
        }
    }
}

void InputSystem::process(Storage<Playable> *playableStorage,
    Storage<Velocity> *velocityStorage, unsigned long long int entityID, KeyBind key
) const
{
    Velocity *entityVelocity = &velocityStorage->getComponentForEntity(entityID);
    Playable *entityPlayable = &playableStorage->getComponentForEntity(entityID);

    entityPlayable->key = key;
    switch (entityPlayable->key) {
    case ARROWLEFT:
        entityVelocity->yOffset = 0;
        entityVelocity->xOffset = (-1);
        break;
    case ARROWRIGHT:
        entityVelocity->yOffset = 0;
        entityVelocity->xOffset = 1;
        break;
    case ARROWUP:
        entityVelocity->xOffset = 0;
        entityVelocity->yOffset = (-1);
        break;
    case ARROWDOWN:
        entityVelocity->xOffset = 0;
        entityVelocity->yOffset = 1;
        break;
    default:
//        velocityStorage->getComponentForEntity(entityID) = Velocity{entityID, 0,
//            0};
        break;
    }
}


