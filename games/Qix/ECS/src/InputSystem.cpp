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

void InputSystem::update(Storage<Playable> *playableStorage, Storage<Path> *pathStorage,
    Storage<Velocity> *velocityStorage, KeyBind key
) const
{
    if (key == NONE)
        return;
    for (auto it : velocityStorage->entityIdxToComponentIdxMap) {
        if (playableStorage->hasEntityComponent(it.first) && pathStorage->hasEntityComponent(it.first)) {
            process(playableStorage, pathStorage, velocityStorage, it.first, key);
        }
    }
}

void InputSystem::process(Storage<Playable> *playableStorage, Storage<Path> *pathStorage,
    Storage<Velocity> *velocityStorage, unsigned long long int entityID, KeyBind key
) const
{
    KeyBind oldKey = playableStorage->getComponentForEntity(entityID).key;
    bool canMakePath = pathStorage->getComponentForEntity(entityID).canMakePath;

    switch (key) {
    case ARROWLEFT:
        if (oldKey == ARROWRIGHT && canMakePath)
            return;
        velocityStorage->getComponentForEntity(entityID).yOffset = 0;
        velocityStorage->getComponentForEntity(entityID).xOffset = (-1);
        break;
    case ARROWRIGHT:
        if (oldKey == ARROWLEFT && canMakePath)
            return;
        velocityStorage->getComponentForEntity(entityID).yOffset = 0;
        velocityStorage->getComponentForEntity(entityID).xOffset = 1;
        break;
    case ARROWUP:
        if (oldKey == ARROWDOWN && canMakePath)
            return;
        velocityStorage->getComponentForEntity(entityID).xOffset = 0;
        velocityStorage->getComponentForEntity(entityID).yOffset = (-1);
        break;
    case ARROWDOWN:
        if (oldKey == ARROWUP && canMakePath)
            return;
        velocityStorage->getComponentForEntity(entityID).xOffset = 0;
        velocityStorage->getComponentForEntity(entityID).yOffset = 1;
        break;
    default:
        break;
    }
    playableStorage->getComponentForEntity(entityID).key = key;
}


