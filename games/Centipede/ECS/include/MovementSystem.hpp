/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP
#define OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"
#include "FollowerSystem.hpp"

class MovementSystem {
    public:
        MovementSystem();
        ~MovementSystem();
        void update(Storage<Position> *positionStorage, Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage,
        Storage<Tag> *typeStorage, FollowerSystem *_follow, Storage<Follower> *followerStorage) const;
    protected:
    private:
        void process(Storage<Position> *positionStorage,
            Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage,
            Storage<Tag> *typeStorage, FollowerSystem *_follow, Storage<Follower> *followerStorage, unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP
