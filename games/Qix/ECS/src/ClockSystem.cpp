/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/ClockSystem.hpp"

ClockSystem::ClockSystem()
{
}

ClockSystem::~ClockSystem()
{
}

void ClockSystem::update(Storage<Clock> *clockStorage)
{
    for (auto & it : clockStorage->entityIdxToComponentIdxMap) {
            process(clockStorage, it.first);
    }
}

void ClockSystem::process(Storage<Clock> *clockStorage, unsigned long long int entityID) const
{
    clockStorage->getComponentForEntity(entityID).tickCount++;
}