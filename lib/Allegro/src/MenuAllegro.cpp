/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/MenuAllegro.hpp"

MenuAllegro::MenuAllegro()
:_font(nullptr), _selectionFont(nullptr)
{
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    _font = al_load_font("assets/font/arcade.ttf", 50, ALLEGRO_ALIGN_CENTER);
    _selectionFont = al_load_font("assets/font/arcade-italic.ttf", 30, ALLEGRO_ALIGN_CENTER);
    if (!_font || !_selectionFont)
        std::cout << "Failed to load font" << std::endl;
}

MenuAllegro::~MenuAllegro()
{
    al_destroy_font(_font);
    al_destroy_font(_selectionFont);
}

void MenuAllegro::displayMenu()
{
}

void MenuAllegro::drawBackgroundBoxes(int activeBox) const
{
    float xStart = 10;
    float yStart = 10;
    float boxLength = 945;
    float boxHeight = 500;
    float offset = 10;
    int count = 0;
    ALLEGRO_COLOR color = al_map_rgb(85,35,35);
    ALLEGRO_COLOR selectedColor = al_map_rgb(133, 55,55);
    ALLEGRO_COLOR blackColor = al_map_rgb(0, 0, 0);

    //draw graphical and game background
    for (float x = xStart; x < 2 * boxLength + 3 * offset; x += boxLength + offset) {
        if (count == activeBox) {
            al_draw_filled_rounded_rectangle(x, yStart, x + boxLength, yStart + boxHeight, 20, 20, selectedColor);
        } else {
            al_draw_filled_rounded_rectangle(x, yStart, x + boxLength, yStart + boxHeight, 20, 20, color);
        }
        al_draw_rounded_rectangle(x, 10, x + boxLength, yStart + boxHeight, 20, 20, blackColor, 3);
        count++;
    }
    //draw graph and game section name
    al_draw_textf(_font, al_map_rgb(255, 255, 255), xStart + boxLength / 2, yStart + offset, ALLEGRO_ALIGN_CENTER, "GRAPHICALS");
    al_draw_textf(_font, al_map_rgb(255, 255, 255), xStart + boxLength + offset + boxLength / 2, yStart + offset, ALLEGRO_ALIGN_CENTER, "GAMES");

    //draw score background
    al_draw_filled_rounded_rectangle(xStart + boxLength + offset, yStart + boxHeight + offset, xStart + (2 * boxLength) + offset,
        yStart + (2 * boxHeight) - offset, 20, 20, color);
    al_draw_rounded_rectangle(xStart + boxLength + offset, yStart + boxHeight + offset, xStart + (2 * boxLength) + offset,
        yStart + (2 * boxHeight) - offset, 20, 20, blackColor, 3);

    //draw score name
    al_draw_textf(_font, al_map_rgb(255, 255, 255), xStart + boxLength + offset + boxLength / 2, yStart + boxHeight + (2 * offset), ALLEGRO_ALIGN_CENTER, "SCORES");

    //draw username background
    if (count == activeBox) {
        al_draw_filled_rectangle(xStart, yStart + boxHeight + offset + 50, xStart + boxLength, yStart + boxHeight + offset + boxHeight / 3,
            selectedColor);
    } else {
        al_draw_filled_rectangle(xStart, yStart + boxHeight + offset + 50, xStart + boxLength, yStart + boxHeight + offset + boxHeight / 3,
            color);
    }
    al_draw_rectangle(xStart, yStart + boxHeight + offset + 50, xStart + boxLength, yStart + boxHeight + offset + boxHeight / 3,
        blackColor, 3);

    //draw play button background
    count++;
    if (count == activeBox) {
        al_draw_filled_circle(xStart + boxLength / 2, yStart + boxHeight + 2 * offset + boxHeight / 2 + 80, 100, selectedColor);
    } else {
        al_draw_filled_circle(xStart + boxLength / 2, yStart + boxHeight + 2 * offset + boxHeight / 2 + 80, 100, color);
    }
    al_draw_circle(xStart + boxLength / 2, yStart + boxHeight + 2 * offset + boxHeight / 2 + 80, 100, blackColor, 3);
    al_draw_arc(xStart + boxLength / 2, yStart + boxHeight + 2 * offset + boxHeight / 2 + 80, 50, 5.1, 5.5, blackColor, 5);
    al_draw_line(xStart + boxLength / 2, yStart + boxHeight + 2 * offset + boxHeight / 2 + 70, xStart + boxLength / 2, yStart + boxHeight + 2 * offset + boxHeight / 2 + 20, blackColor, 5);
}

void MenuAllegro::drawSelectionList(std::vector<std::string> boxVector,
    int activeBox, float xStart, float yStart
) const
{
    bool reverse = false;
    int count = 0;
    float boxLength = 945;
    float boxHeight = 500;
    float offset = 10;
    int size = 0;
    float triangleLength = boxLength - (4 * offset);
    float triangleHeight = 0;
    ALLEGRO_COLOR color = al_map_rgb(156,50,50);
    ALLEGRO_COLOR selectedColor = al_map_rgb(199,64,64);
    ALLEGRO_COLOR blackColor = al_map_rgb(0, 0, 0);

    for (long unsigned int i = 0; i <= boxVector.size(); i++) {
        size += i % 2;
    }
    triangleHeight = ((boxHeight - yStart) / size) - (2 * offset);
    //al_draw_triangle(xStart, yStart, xStart + triangleLength, yStart, xStart + triangleLength, yStart + triangleHeight, blackColor, 3);
    //al_draw_triangle(xStart, yStart + offset, xStart + triangleLength, yStart + triangleHeight + offset, xStart, yStart + offset + triangleHeight, blackColor, 3);
    for (auto &content: boxVector) {
        if (!reverse) {
            if (count == activeBox) {
                al_draw_filled_triangle(xStart, yStart, xStart + triangleLength, yStart,
                xStart + triangleLength, yStart + triangleHeight, selectedColor);
            } else {
                al_draw_filled_triangle(xStart, yStart, xStart + triangleLength, yStart,
                    xStart + triangleLength, yStart + triangleHeight, color);
            }
            al_draw_triangle(xStart, yStart, xStart + triangleLength, yStart,
                xStart + triangleLength, yStart + triangleHeight, blackColor,
                3);
            al_draw_text(_selectionFont, al_map_rgb(255, 255, 255), xStart + triangleLength - (2 * offset), yStart + offset, ALLEGRO_ALIGN_RIGHT, content.c_str());
        } else {
            if (count == activeBox) {
                al_draw_filled_triangle(xStart, yStart + offset, xStart + triangleLength,
                    yStart + triangleHeight + offset, xStart,
                    yStart + offset + triangleHeight, selectedColor);
            } else {
                al_draw_filled_triangle(xStart, yStart + offset, xStart + triangleLength,
                    yStart + triangleHeight + offset, xStart,
                    yStart + offset + triangleHeight, color);
            }
            al_draw_triangle(xStart, yStart + offset, xStart + triangleLength,
                yStart + triangleHeight + offset, xStart,
                yStart + offset + triangleHeight, blackColor, 3);
            al_draw_text(_selectionFont, al_map_rgb(255, 255, 255), xStart + offset, yStart + triangleHeight - (3 * offset), ALLEGRO_ALIGN_LEFT, content.c_str());
        }
        reverse = !reverse;
        if (count % 2 != 0)
            yStart += triangleHeight + (2 * offset);
        count++;
    }
}

void MenuAllegro::drawUsername(const std::string &username) const
{
    al_draw_textf(_font, al_map_rgb(255, 255, 255), 20, 610, ALLEGRO_ALIGN_LEFT, "Username: %s", username.c_str());
}

void MenuAllegro::drawScoreBoard(std::vector<std::pair<std::string, std::string>> scores) const
{
    int count = 1;
    float xStart = 980;
    float yStart = 610;
    float boxLength = 945;

    for (auto &it: scores) {
        if (count > 5) {
            break;
        }
        al_draw_textf(_font, al_map_rgb(255, 255, 255), xStart, yStart, ALLEGRO_ALIGN_LEFT, "%d", count);
        al_draw_textf(_font, al_map_rgb(255, 255, 255), xStart + (boxLength / 2), yStart, ALLEGRO_ALIGN_CENTER, "%s", it.first.c_str());
        al_draw_textf(_font, al_map_rgb(255, 255, 255), xStart + (boxLength - 50), yStart, ALLEGRO_ALIGN_RIGHT, "%s", it.second.c_str());
        yStart += 50;
        count++;
    }
}
