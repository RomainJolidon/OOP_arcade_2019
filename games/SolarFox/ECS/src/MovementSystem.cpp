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

void MovementSystem::update(Storage<Position> *positionStorage, Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage) const
{
    for (auto it : clockStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->hasEntityComponent(it.first) && velocityStorage->hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, clockStorage, it.first);
        }
    }
}

void MovementSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, unsigned long long int entityID) const
{
    if (clockStorage->getComponentForEntity(entityID).tickCount >= clockStorage->getComponentForEntity(entityID).limit) {
        positionStorage->getComponentForEntity(
            entityID).x += velocityStorage->getComponentForEntity(
            entityID).xOffset;
        positionStorage->getComponentForEntity(
            entityID).y += velocityStorage->getComponentForEntity(
            entityID).yOffset;
        clockStorage->getComponentForEntity(entityID).tickCount = 0;
    }
}



