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

struct Position {
    unsigned long long int entityId;
    int x;
    int y;
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

struct AI {
    unsigned long long int entityId;
    int randomAction;
};


struct Playable {
    unsigned long long int entityId;
    KeyBind key;
};

struct Walkable {
    unsigned long long int entityId;
    int height;
    int width;
};

struct Clock {
    unsigned long long int entityId;
    unsigned int tickCount;
    unsigned long long int limit;
};

struct Follower {
    unsigned long long int entityId;
    unsigned long long int targetId;
    int xSave;
    int ySave;
};

struct Collectible {
    unsigned long long int entityId;
};

struct Shooting {
    unsigned long long int entityId;
    TypeEntity target;
    unsigned int tickCount;
    unsigned long long int limit;
};

struct Damage {
    unsigned long long int entityId;
    int health;
};

#endif //OOP_ARCADE_2019_COMPONENTS_HPP
