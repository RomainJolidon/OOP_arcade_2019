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
        void update(
            Storage<Position> *positionStorage,
            Storage<Velocity> *velocityStorage,
            Storage<Collider> *colliderStorage,
            Storage<Tag> *typeStorage,
            Storage<Playable> *playableStorage,
            Storage<Bonus> *bonusStorage
            ) const;
    protected:
    private:
        void process(Storage<Position> *positionStorage, 
            Storage<Velocity> *velocityStorage,
            Storage<Collider> *colliderStorage,
            Storage<Tag> *typeStorage,
            Storage<Playable> *playableStorage,
            Storage<Bonus> *bonusStorage,
            unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_COLLISIONSYSTEM_HPP
