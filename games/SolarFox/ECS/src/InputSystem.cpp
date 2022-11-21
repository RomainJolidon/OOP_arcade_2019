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
    for (auto it : velocityStorage->entityIdxToComponentIdxMap) {
        if (playableStorage->hasEntityComponent(it.first)) {
            process(playableStorage, velocityStorage, it.first, key);
        }
    }
}

void InputSystem::process(Storage<Playable> *playableStorage,
    Storage<Velocity> *velocityStorage, unsigned long long int entityID, KeyBind key
) const
{
    playableStorage->getComponentForEntity(entityID).key = key;
    switch (playableStorage->getComponentForEntity(entityID).key) {
    case ARROWLEFT:
        velocityStorage->getComponentForEntity(entityID).yOffset = 0;
        velocityStorage->getComponentForEntity(entityID).xOffset = (-1);
        break;
    case ARROWRIGHT:
        velocityStorage->getComponentForEntity(entityID).yOffset = 0;
        velocityStorage->getComponentForEntity(entityID).xOffset = 1;
        break;
    case ARROWUP:
        velocityStorage->getComponentForEntity(entityID).xOffset = 0;
        velocityStorage->getComponentForEntity(entityID).yOffset = (-1);
        break;
    case ARROWDOWN:
        velocityStorage->getComponentForEntity(entityID).xOffset = 0;
        velocityStorage->getComponentForEntity(entityID).yOffset = 1;
        break;
    default:
//        velocityStorage->getComponentForEntity(entityID) = Velocity{entityID, 0,
//            0};
        break;
    }
}


