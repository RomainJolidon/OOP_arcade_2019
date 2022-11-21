/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_LIBALLEGRO_HPP
#define OOP_ARCADE_2019_LIBALLEGRO_HPP

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "IDisplayModule.hpp"
#include "MenuAllegro.hpp"

class LibAllegro: public IDisplayModule {
    public:
    LibAllegro();

    ~LibAllegro();
    bool isOpen() const;
    void drawEntity(const Entity &ent_1);
    void initWindow();
    void destroyWindow();
    KeyBind inputListener(const ALLEGRO_EVENT& event) const;
    KeyBind eventListener();
    void oneCycleDisplay() const;
    void displayMenu(const MenuInfo &menuInfo);
    void oneCycleClear();

    protected:
    private:
    std::string _name;
    ALLEGRO_DISPLAY *_window;
    ALLEGRO_EVENT_QUEUE  *_event_queue;
    ALLEGRO_TIMER *_timer;

    bool _running;
    bool _redraw;

    MenuAllegro menu;
};

#endif //OOP_ARCADE_2019_LIBALLEGRO_HPP
