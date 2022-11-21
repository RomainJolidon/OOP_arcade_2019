/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_CLOCKSYSTEM_HPP
#define OOP_ARCADE_2019_CLOCKSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class ClockSystem {
    public:
    ClockSystem();
    ~ClockSystem();
    void update(Storage<Clock> *clockStorage);

    protected:
    private:
    void process(Storage<Clock> *clockStorage, unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_CLOCKESYSTEM_HPP
