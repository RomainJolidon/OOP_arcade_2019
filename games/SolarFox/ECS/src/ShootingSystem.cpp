/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ShootingSystem
*/

#include "../include/ShootingSystem.hpp"

ShootingSystem::ShootingSystem() = default;

ShootingSystem::~ShootingSystem() = default;

void ShootingSystem::update(
    Storage<Shooting> *shootingStorage,
    Storage<Clock> *clockStorage,
    Storage<Tag> *typeStorage,
    Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage
) const {
    for (auto it : shootingStorage->entityIdxToComponentIdxMap) {
        if (clockStorage->hasEntityComponent(it.first)) {
            process(shootingStorage, clockStorage, typeStorage, positionStorage, velocityStorage, it.first);
        }
    }
}

void ShootingSystem::process(
    Storage<Shooting> *shootingStorage,
    Storage<Clock> *clockStorage,
    Storage<Tag> *typeStorage,
    Storage<Position> *positionStorage,
    Storage<Velocity> *velocityStorage,
    unsigned long long int entityID
) const {
    shootingStorage->getComponentForEntity(entityID).tickCount++;
    if (shootingStorage->getComponentForEntity(entityID).tickCount >= shootingStorage->getComponentForEntity(entityID).limit) {
        shootingStorage->removeComponentForEntity(entityID);
        clockStorage->removeComponentForEntity(entityID);
        typeStorage->removeComponentForEntity(entityID);
        positionStorage->removeComponentForEntity(entityID);
        velocityStorage->removeComponentForEntity(entityID);
    }
}