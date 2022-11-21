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

class FollowerSystem {
    public:
    FollowerSystem();
    ~FollowerSystem();
    void update(Storage<Follower> *FollowerStorage, Storage<Velocity> *velocityStorage) const;

    protected:
    private:
    void process(Storage<Follower> *FollowerStorage, Storage<Velocity> *velocityStorage, unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_FOLLOWERSYSTEM_HPP
