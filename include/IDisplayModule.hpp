/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019_bootstrap
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Entity.hpp"
#include "MenuInfo.hpp"

enum KeyBind {
    ARROWLEFT,
    ARROWRIGHT,
    ARROWUP,
    ARROWDOWN,
    ENTER,
    RETURN,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    SPACE,
    EXIT,
    PREV_LIB,
    PREV_GAME,
    NEXT_LIB,
    NEXT_GAME,
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    RESTART,
    VALID,
    PAUSE,
    MENU,
    NONE,
    NO_EVENT
};

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;
        virtual bool isOpen() const = 0;
        virtual void initWindow() = 0;
        virtual void destroyWindow() = 0;
        virtual void drawEntity(const Entity &ent_1) = 0;
        virtual KeyBind eventListener() = 0;
        virtual void oneCycleDisplay() const = 0;
        virtual void displayMenu(const MenuInfo &menuInfo) = 0;
        virtual void oneCycleClear() = 0;
};
#endif /* !IDISPLAYMODULE_HPP_ */
