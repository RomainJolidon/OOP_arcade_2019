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

class MovementSystem {
    public:
        MovementSystem();
        ~MovementSystem();
        void update(Storage<Position> *positionStorage, Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, Storage<Tag> *typeStorage, Storage<Path> *pathStorage) const;
    protected:
    private:
        void process(Storage<Position> *positionStorage,
            Storage<Velocity> *velocityStorage, Storage<Clock> *clockStorage, Storage<Tag> *typeStorage, Storage<Path> *pathStorage, unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP
