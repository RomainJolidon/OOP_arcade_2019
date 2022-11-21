/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef __IENTITYX__HPP
#define __IENTITYX__HPP

enum TypeEntity {
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    ENEMY_1,
    ENEMY_2,
    ENEMY_3,
    WALL_1,
    WALL_2,
    WALL_3,
    WALL_4,
    FLOOR,
    BONUS_1,
    BONUS_2,
    BONUS_3,
    PROJECTILE,
    MAP,
    BACKGROUND,
    GAME_WON,
    GAME_LOST,
    TITLEMENU,
    TITLEGAME,
    ERROR,
    BULLET
};

class IEntity {
    public:
    virtual ~IEntity() = default;
    virtual TypeEntity getType() const = 0;
    virtual void setType(TypeEntity type) = 0;
    virtual float getPosX() const = 0;
    virtual void setPosX(float x) = 0;
    virtual float getPosY() const = 0;
    virtual void setPosY(float y) = 0;
    virtual void updatePos(float x, float y) = 0;
    private:
    protected:
};

#endif //OOP_ARCADE_2019_IENTITYX_HPP
