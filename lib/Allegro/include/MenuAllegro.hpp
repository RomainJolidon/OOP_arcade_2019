/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_MENUALLEGRO_HPP
#define OOP_ARCADE_2019_MENUALLEGRO_HPP

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <vector>
#include <iostream>

class MenuAllegro {
    public:
    MenuAllegro();
    void displayMenu();
    void drawBackgroundBoxes(int activeBox) const;
    void drawSelectionList(std::vector<std::string> boxVector, int activeBox, float xStart, float yStart) const;
    void drawUsername(const std::string& username) const;
    void drawScoreBoard(std::vector<std::pair<std::string, std::string>> scores) const;
    ~MenuAllegro();

    protected:
    private:
    ALLEGRO_FONT *_font;
    ALLEGRO_FONT *_selectionFont;

};

#endif //OOP_ARCADE_2019_MENUALLEGRO_HPP
