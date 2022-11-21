/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ShootingSystem
*/

#ifndef SHOOTINGSYSTEM_HPP_
#define SHOOTINGSYSTEM_HPP_

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class ShootingSystem {
    public:
        ShootingSystem();
        ~ShootingSystem();
        void update(
            Storage<Shooting> *shootingStorage,
            Storage<Clock> *clockStorage,
            Storage<Tag> *typeStorage,
            Storage<Position> *positionStorage,
            Storage<Velocity> *velocityStorage
        ) const;
    protected:
    private:
    void process(
        Storage<Shooting> *shootingStorage,
        Storage<Clock> *clockStorage,
        Storage<Tag> *typeStorage,
        Storage<Position> *positionStorage,
        Storage<Velocity> *velocityStorage,
        unsigned long long int entityID
    ) const;
};

#endif /* !SHOOTINGSYSTEM_HPP_ */