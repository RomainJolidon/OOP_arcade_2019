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
    Position *entityPosition = &positionStorage->getComponentForEntity(entityID);
    Velocity *entityVelocity = &velocityStorage->getComponentForEntity(entityID);
    Clock *entityClock = &clockStorage->getComponentForEntity(entityID);

    if (entityClock->tickCount >= entityClock->limit) {
        if (entityPosition->x >= 20) {
            entityPosition->x = 0;
            entityPosition->y = 9;
        }
        else if (entityPosition->x <= 0) {
            entityPosition->x = 20;
            entityPosition->y = 9;
        }
        entityPosition->x += entityVelocity->xOffset;
        entityPosition->y += entityVelocity->yOffset;
        entityClock->tickCount = 0;
    }
}



