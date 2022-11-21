/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "Entity.hpp"

Entity::Entity(TypeEntity type, float x, float y)
    : _type(type), _x(x), _y(y)
{
}

Entity::~Entity()
= default;

TypeEntity Entity::getType() const
{
    return _type;
}

void Entity::setType(TypeEntity type)
{
    _type = type;
}


void Entity::setPosX(float x)
{
    _x = x;
}

float Entity::getPosY() const
{
    return _y;
}

void Entity::setPosY(float y)
{
    _y = y;
}

void Entity::updatePos(float x, float y)
{
    _y = y;
    _x = x;
}

float Entity::getPosX() const
{
    return _x;
}