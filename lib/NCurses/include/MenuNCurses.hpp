/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** MenuNCurses
*/

#ifndef MENUNCURSES_HPP_
#define MENUNCURSES_HPP_

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <ncurses.h>
#include "MenuInfo.hpp"
#include "colorPair.hpp"

typedef enum {LIBS, GAMES, OTHER} boxtype_t;

class MenuNCurses {
    public:
        MenuNCurses();
        ~MenuNCurses();
        void display(const MenuInfo&);
        void drawHolder();
        void drawRect(int baseX, int baseY, int width, int height);
        void drawBox(std::vector<std::string>, boxtype_t, int, int);
        void drawBox(std::vector<std::pair<std::string, std::string>>);
        void drawBox(std::string, int);
        void drawBox(int);
    protected:
    private:
};

#endif /* !MENUNCURSES_HPP_ */