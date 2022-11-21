/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibNCurses
*/

#ifndef LIBNCURSES_HPP_
#define LIBNCURSES_HPP_

#include <ncurses.h>
#include <chrono>
#include "MenuNCurses.hpp"
#include "IDisplayModule.hpp"
#include "MenuInfo.hpp"
#include "colorPair.hpp"

class LibNCurses: public IDisplayModule {
    public:
        explicit LibNCurses();
        ~LibNCurses() override ;
        void initWindow();
        void destroyWindow();
        bool isOpen() const override ;
        void drawEntity(const Entity &ent_1) override ;
        KeyBind inputListener() const;
        KeyBind eventListener()  override ;
        void oneCycleDisplay() const override ;
        void oneCycleClear() override ;
        void displayMenu(const MenuInfo &menuInfo) override ;


    private:
        std::string _name;
        bool _isopen;
        MenuNCurses _menu;
};

#endif /* !LIBNCURSES_HPP_ */