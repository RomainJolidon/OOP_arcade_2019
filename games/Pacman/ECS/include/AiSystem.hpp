/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_AISYSTEM_HPP
#define OOP_ARCADE_2019_AISYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class AISystem {
    public:
    AISystem();
    ~AISystem();
    void update(Storage<AI> *AIStorage, Storage<Velocity> *velocityStorage) const;
    protected:
    private:
    void process(Storage<AI> *AIStorage, Storage<Velocity> *velocityStorage, unsigned long long int entityID) const;

};

#endif //OOP_ARCADE_2019_AISYSTEM_HPP
