/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_COMPONENTS_HPP
#define OOP_ARCADE_2019_COMPONENTS_HPP

#include <IEntity.hpp>
#include <IDisplayModule.hpp>

enum Effect {
    BONUS1,
    SUPERBONUS1,
    SUPERBONUS2,
    NOEFFECT,
};


struct Position {
    unsigned long long int entityId;
    int x;
    int y;
    int initialPosX;
    int initialPosY;
};

struct Velocity {
    unsigned long long int entityId;
    int xOffset;
    int yOffset;
};

struct Collider {
    unsigned long long int entityId;
    int height;
    int width;
};

struct Tag {
    unsigned long long int entityId;
    TypeEntity type;
};

struct Bonus {
    unsigned long long int entityId;
    Effect effect;
};

struct AI {
    unsigned long long int entityId;
    int randomAction;
};

struct Playable {
    unsigned long long int entityId;
    KeyBind key;
    Effect effect;
};

struct Clock {
    unsigned long long int entityId;
    int tickCount;
    int limit;
};

#endif //OOP_ARCADE_2019_COMPONENTS_HPP
