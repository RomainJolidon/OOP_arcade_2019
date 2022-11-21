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

void AISystem::update(Storage<AI> *AIStorage, Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, const std::vector<std::pair<int, int>> &borderVector) const
{
    for (auto it : AIStorage->entityIdxToComponentIdxMap) {
        if (velocityStorage->hasEntityComponent(it.first)) {
            process(velocityStorage, positionStorage, borderVector, it.first);
        }
    }
}

void AISystem::process(Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, const std::vector<std::pair<int, int>> &borderVector, unsigned long long int entityID
) const
{
    int x = positionStorage->getComponentForEntity(entityID).x;
    int y = positionStorage->getComponentForEntity(entityID).y;
    bool foundPos = false;
    std::pair<int, int> closest(999, 999);
    std::pair<int, int> closestPos(999, 999);

    for (auto &pos: borderVector) {
        if (foundPos) {
            velocityStorage->getComponentForEntity(entityID).xOffset = getNormalizedVelocity(pos.first, x);
            velocityStorage->getComponentForEntity(entityID).yOffset = getNormalizedVelocity(pos.second, y);
            return;
        }
        if (x == pos.first && y == pos.second)
            foundPos = true;
    }
    if (foundPos) {
        velocityStorage->getComponentForEntity(entityID).xOffset = getNormalizedVelocity(borderVector.begin()->first, x);
        velocityStorage->getComponentForEntity(entityID).yOffset = getNormalizedVelocity(borderVector.begin()->second, y);
        return;
    }

    //find to closest position to border
    for (auto &pos: borderVector) {
        if (x - pos.first < closest.first) {
            if (y > pos.second) {
                if (y - pos.second < closest.second) {
                    closest.first = x - pos.first;
                    closest.second = y - pos.second;
                    closestPos.first = pos.first;
                    closestPos.second = pos.second;
                }
            } else {
                if (pos.second - y < closest.second) {
                    closest.first = x - pos.first;
                    closest.second = pos.second - y;
                    closestPos.first = pos.first;
                    closestPos.second = pos.second;
                }
            }
        } else {
            if (y > pos.second) {
                if (y - pos.second < closest.second) {
                    closest.first = pos.first - x;
                    closest.second = y - pos.second;
                    closestPos.first = pos.first;
                    closestPos.second = pos.second;
                }
            } else {
                if (pos.second - y < closest.second) {
                    closest.first = pos.first - x;
                    closest.second = pos.second - y;
                    closestPos.first = pos.first;
                    closestPos.second = pos.second;
                }
            }
        }
        velocityStorage->getComponentForEntity(entityID).xOffset = getNormalizedVelocity(closestPos.first, x);
        velocityStorage->getComponentForEntity(entityID).yOffset = getNormalizedVelocity(closestPos.second, y);
    }
}

int AISystem::getNormalizedVelocity(int nb1, int nb2) const
{
    int res = nb1 - nb2;
    int abs = res;

    if (abs == 0)
        return (0);
    if (abs < 0)
        abs = -abs;
    return (res / abs);
}
