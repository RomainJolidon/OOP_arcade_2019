/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_COLLISIONSYSTEM_HPP
#define OOP_ARCADE_2019_COLLISIONSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class CollisionSystem {
    public:
        CollisionSystem();
        ~CollisionSystem();
        bool update(
            Storage<Position> *positionStorage,
            Storage<Velocity> *velocityStorage,
            Storage<Collider> *colliderStorage,
            Storage<Shooting> *shootingStorage,
            Storage<Tag> *typeStorage,
            Storage<Clock> *clockStorage,
            Storage<Follower> *followerStorage,
            Storage<Damage> *dmgStorage,
            Storage<Walkable> *walkableStorage
        ) const;
    protected:
    private:
        bool process(
            Storage<Position> *positionStorage,
            Storage<Velocity> *velocityStorage,
            Storage<Collider> *colliderStorage,
            Storage<Shooting> *shootingStorage,
            Storage<Tag> *typeStorage,
            Storage<Clock> *clockStorage,
            Storage<Follower> *followerStorage,
            Storage<Damage> *dmgStorage,
            Storage<Walkable> *walkableStorage,
            unsigned long long int entityID
        ) const;
};

#endif //OOP_ARCADE_2019_COLLISIONSYSTEM_HPP
