/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "../include/MovementSystem.hpp"

MovementSystem::MovementSystem()
= default;

MovementSystem::~MovementSystem()
= default;

void MovementSystem::update(Storage<Position> *positionStorage, Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, Storage<Tag> *typeStorage, Storage<Path> *pathStorage) const
{
    for (auto it : clockStorage->entityIdxToComponentIdxMap) {
        if (positionStorage->hasEntityComponent(it.first) && velocityStorage->hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, clockStorage, typeStorage, pathStorage, it.first);
        }
    }
}

void MovementSystem::process(Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, Storage<Tag> *typeStorage, Storage<Path> *pathStorage, unsigned long long int entityID) const
{
    TypeEntity type = ERROR;


    if (clockStorage->getComponentForEntity(entityID).tickCount >= clockStorage->getComponentForEntity(entityID).limit) {
        if (velocityStorage->getComponentForEntity(entityID).xOffset == 0 && velocityStorage->getComponentForEntity(entityID).yOffset == 0)
            return;
        positionStorage->getComponentForEntity(
            entityID).x += velocityStorage->getComponentForEntity(
            entityID).xOffset;
        positionStorage->getComponentForEntity(
            entityID).y += velocityStorage->getComponentForEntity(
            entityID).yOffset;

        if (pathStorage->hasEntityComponent(entityID)) {
            for (auto it: positionStorage->entityIdxToComponentIdxMap) {
                if (it.first != entityID && positionStorage->getComponentForEntity(entityID).x == positionStorage->getComponentForEntity(it.first).x &&
                    positionStorage->getComponentForEntity(entityID).y == positionStorage->getComponentForEntity(it.first).y) {
                    type = typeStorage->getComponentForEntity(it.first).type;
                    break;
                }
            }
            if (type == WALL_1 || type == WALL_2 || type == WALL_3) {
                velocityStorage->getComponentForEntity(entityID).xOffset = 0;
                velocityStorage->getComponentForEntity(entityID).yOffset = 0;
                pathStorage->getComponentForEntity(entityID).canMakePath = false;
                if (pathStorage->getComponentForEntity(entityID).path.size() <= 1) {
                    pathStorage->getComponentForEntity(entityID).path.clear();
                }
            } else {
                pathStorage->getComponentForEntity(entityID).canMakePath = true;
            }
            pathStorage->getComponentForEntity(entityID).path.emplace_back(positionStorage->getComponentForEntity(entityID).x, positionStorage->getComponentForEntity(entityID).y);
        }
        clockStorage->getComponentForEntity(entityID).tickCount = 0;
    }
}

