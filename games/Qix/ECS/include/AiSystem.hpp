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
    void update(Storage<AI> *AIStorage, Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, const std::vector<std::pair<int, int>> &borderVector) const;
    protected:
    private:
    void process(Storage<Velocity> *velocityStorage, Storage<Position> *positionStorage, const std::vector<std::pair<int, int>> &borderVector,unsigned long long int entityID) const;
    int getNormalizedVelocity(int nb1, int nb2) const;

};

#endif //OOP_ARCADE_2019_AISYSTEM_HPP
