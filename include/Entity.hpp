/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_ENTITY_HPP
#define OOP_ARCADE_2019_ENTITY_HPP

#include "IEntity.hpp"

class Entity : public IEntity{
    public:
    Entity(TypeEntity type, float x, float y);
    ~Entity() override;
    TypeEntity getType() const override ;
    void setType(TypeEntity type) override;
    float getPosX() const override;
    void setPosX(float x) override;
    float getPosY() const override;
    void setPosY(float y) override;
    void updatePos(float x, float y) override;
    private:
    protected:
    TypeEntity _type;
    float _x;
    float _y;
};
#endif //OOP_ARCADE_2019_ENTITY_HPP
