/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibNCurses
*/

#include "../include/LibNCurses.hpp"

LibNCurses::LibNCurses():
_name("LibNCurses"), _isopen(true), _menu(MenuNCurses())
{
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    nodelay(stdscr, true);
    start_color();
    init_pair(cursesColor::Entity::PLAYER_1, COLOR_BLACK, COLOR_WHITE);
    init_pair(cursesColor::Entity::PLAYER_2, COLOR_BLACK, COLOR_WHITE);
    init_pair(cursesColor::Entity::PLAYER_3, COLOR_BLACK, COLOR_WHITE);
    init_pair(cursesColor::Entity::ENEMY_1, COLOR_BLACK, COLOR_RED);
    init_pair(cursesColor::Entity::ENEMY_2, COLOR_BLACK, COLOR_RED);
    init_pair(cursesColor::Entity::ENEMY_3, COLOR_BLACK, COLOR_RED);
    init_pair(cursesColor::Entity::WALL_1, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(cursesColor::Entity::WALL_2, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(cursesColor::Entity::WALL_3, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(cursesColor::Entity::WALL_4, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(cursesColor::Entity::FLOOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(cursesColor::Entity::BONUS_1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(cursesColor::Entity::BONUS_2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(cursesColor::Entity::BONUS_3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(cursesColor::Entity::PROJECTILE, COLOR_BLACK, COLOR_BLUE);
    init_pair(cursesColor::Entity::ERROR, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(cursesColor::Entity::BULLET, COLOR_BLACK, COLOR_BLUE);
    init_pair(cursesColor::Text::T_BLACK, COLOR_BLACK, COLOR_WHITE);
    init_pair(cursesColor::Text::T_RED, COLOR_RED, COLOR_WHITE);
    init_pair(cursesColor::Text::T_GREEN, COLOR_GREEN, COLOR_WHITE);
    init_pair(cursesColor::Text::T_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(cursesColor::Text::T_BLUE, COLOR_BLUE, COLOR_WHITE);
    init_pair(cursesColor::Text::T_MAGENTA, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(cursesColor::Text::T_CYAN, COLOR_CYAN, COLOR_WHITE);
    init_pair(cursesColor::Text::T_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(cursesColor::Line::L_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(cursesColor::Line::L_RED, COLOR_RED, COLOR_BLACK);
    init_pair(cursesColor::Line::L_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(cursesColor::Line::L_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(cursesColor::Line::L_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(cursesColor::Line::L_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(cursesColor::Line::L_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(cursesColor::Line::L_WHITE, COLOR_WHITE, COLOR_BLACK);
}

LibNCurses::~LibNCurses() {
    endwin();
}

void LibNCurses::initWindow()
{
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    nodelay(stdscr, true);
    start_color();
}

void LibNCurses::destroyWindow()
{
    endwin();
}

KeyBind LibNCurses::inputListener() const {
   //A VOIR
   return (KeyBind::NONE);
}

void LibNCurses::oneCycleDisplay() const
{
    if (this->_isopen) {
        refresh();
    }
}

void LibNCurses::oneCycleClear()
{
    if (this->_isopen) {
        erase();
    }
}

void LibNCurses::displayMenu(const MenuInfo &menuInfo) {
    this->oneCycleClear();
    this->_menu.display(menuInfo);
    this->oneCycleDisplay();
}

KeyBind LibNCurses::eventListener()
{
    int c = getch();

    if (c == 27) {
        this->_isopen = false;
        return KeyBind::NONE;
    }
    switch (c) {
    case KEY_LEFT:
        return KeyBind::ARROWLEFT;
    case KEY_RIGHT:
        return KeyBind::ARROWRIGHT;
    case KEY_UP:
        return KeyBind::ARROWUP;
    case KEY_DOWN:
        return KeyBind::ARROWDOWN;
    case 10:
        return KeyBind::ENTER;
    case KEY_BACKSPACE:
        return KeyBind::RETURN;
    case KEY_F(1):
        return KeyBind ::F1;
    case KEY_F(2):
        return KeyBind ::F2;
    case KEY_F(3):
        return KeyBind ::F3;
    case KEY_F(4):
        return KeyBind ::F4;
    case KEY_F(5):
        return KeyBind ::F5;
    case KEY_F(6):
        return KeyBind ::F6;
    case KEY_F(7):
        return KeyBind ::F7;
    default:
        break;
    }
    for (int i = 'a'; i <= 'z'; i++) {
        if (i == c)
            return static_cast<KeyBind>(c - 'a' + 6);
    }
    return KeyBind::NONE;
}

bool LibNCurses::isOpen() const
{
    return (this->_isopen);
}

void LibNCurses::drawEntity(const Entity &ent_1)
{
    int x, y;
    short entity_color;

    if (ent_1.getType() + 16 >= 33)
        entity_color = cursesColor::Entity::ERROR;
    else
        entity_color = static_cast<cursesColor::Entity>(16 + ent_1.getType());
    x = ent_1.getPosX();
    y = ent_1.getPosY();
    attron(COLOR_PAIR(entity_color));
    mvaddch(y, (x * 2), entity_color == cursesColor::Entity::ERROR ? 'X' : ' ');
    mvaddch(y, (x * 2) + 1, entity_color == cursesColor::Entity::ERROR ? 'X' : ' ');
    attroff(COLOR_PAIR(entity_color));
}

extern "C" IDisplayModule *entryPoint()
{
    return (new LibNCurses);
}