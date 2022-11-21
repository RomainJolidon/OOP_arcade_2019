/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_FOLLOWERSYSTEM_HPP
#define OOP_ARCADE_2019_FOLLOWERSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"
#include <algorithm>

class FollowerSystem {
    public:
    FollowerSystem();
    ~FollowerSystem();
    void update(Storage<Follower> *FollowerStorage, Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, unsigned long long int headID);
    void authorize();

    protected:
    private:
    void process(Storage<Follower> *FollowerStorage, Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, unsigned long long int entityID) const;
    bool _authorized;
};

#endif //OOP_ARCADE_2019_FOLLOWERSYSTEM_HPP
