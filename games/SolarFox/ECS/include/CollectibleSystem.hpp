/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_COLELCTIBLESYSTEM_HPP
#define OOP_ARCADE_2019_COLLECTIBLESYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class CollectibleSystem {
    public:
    CollectibleSystem();
    ~CollectibleSystem();
    bool update(Storage<Collectible> *collectibleStorage, Storage<Tag> *typeStorage, Storage<Position> *positionStorage, Storage<Playable> *playerStorage);

    protected:
    private:
    bool process(Storage<Collectible> *collectibleStorage, Storage<Tag> *typeStorage, Storage<Position> *positionStorage, unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_COLLECTIBLESYSTEM_HPP
