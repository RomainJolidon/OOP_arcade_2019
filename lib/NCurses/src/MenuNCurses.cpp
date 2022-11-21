/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** MenuNCurses
*/

#include "../include/MenuNCurses.hpp"

MenuNCurses::MenuNCurses() {
}

MenuNCurses::~MenuNCurses() {
}

void MenuNCurses::drawHolder() {
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, COLS - 1, ACS_URCORNER);
    mvaddch(LINES - 2, 0, ACS_LLCORNER);
    mvaddch(LINES - 2, COLS - 1, ACS_LRCORNER);
    for (int x = 1; x < COLS - 1; x++) {
        mvaddch(0, x, ACS_HLINE);
        mvaddch(LINES - 2, x, ACS_HLINE);
    }
    for (int y = 1; y < LINES - 2; y++) {
        mvaddch(y, 0, ACS_VLINE);
        mvaddch(y, COLS - 1, ACS_VLINE);
    }
    mvaddch(0, (COLS / 2) - 21, ACS_RTEE);
    mvaddch(0, (COLS / 2) + 20, ACS_LTEE);
    mvaddch(1, (COLS / 2) - 21, ACS_LLCORNER);
    mvaddch(1, (COLS / 2) + 20, ACS_LRCORNER);
    for (int x = (COLS / 2) - 20; x != (COLS / 2) + 20; x++)
        mvaddch(1, x, ACS_HLINE);
    mvprintw(0, (COLS / 2) - 20, " ARCADE PAR BOURGAFF, EMOLITT ET COURBE ");
}

void MenuNCurses::drawRect(int baseX, int baseY, int width, int height) {
    for (int x = baseX; x < baseX + width; x++) {
        mvaddch(baseY, x, ACS_HLINE);
        mvaddch(baseY + height, x, ACS_HLINE);
    }
    for (int y = baseY; y < baseY + height; y++) {
        mvaddch(y, baseX, ACS_VLINE);
        mvaddch(y, baseX + width, ACS_VLINE);
    }
    mvaddch(baseY, baseX, ACS_ULCORNER);
    mvaddch(baseY, baseX + width, ACS_URCORNER);
    mvaddch(baseY + height, baseX, ACS_LLCORNER);
    mvaddch(baseY + height, baseX + width, ACS_LRCORNER);
}

void MenuNCurses::drawBox(std::vector<std::string> list, boxtype_t type, int idx, int activeBox) {
    int x = ((type == LIBS) ? 1 : (COLS / 2)) + ((type == GAMES && COLS % 2 != 0) ? 1 : 0);
    int y = 2;
    int w = (COLS / 2) - 2 + ((type == LIBS && COLS % 2 != 0) ? 1 : 0);
    int h = ((LINES - 5) / 2) - ((LINES % 2 != 0) ? 1 : 0);
    int index = 0;

    attron((activeBox == type) ? A_NORMAL : A_DIM);
    if (activeBox == type)
        attron(COLOR_PAIR(cursesColor::Line::L_GREEN));
    this->drawRect(x, y, w, h);
    if (activeBox == type)
        attroff(COLOR_PAIR(cursesColor::Line::L_GREEN));
    attroff((activeBox == type) ? A_NORMAL : A_DIM);
    attron((activeBox == type) ? A_STANDOUT : A_NORMAL);
    mvprintw(y, x + 1, (type == LIBS) ? " Graphic libs " : " Games ");
    attroff((activeBox == type) ? A_STANDOUT : A_NORMAL);
    x += 2;
    y += 2;
    index = 0;
    for (auto &it: list) {
        attron((idx == index) ? A_STANDOUT : A_NORMAL);
        mvprintw(y + index, x, it.c_str());
        attroff((idx == index) ? A_STANDOUT : A_NORMAL);
        index++;
    }
}

void MenuNCurses::drawBox(std::vector<std::pair<std::string, std::string>> scores) {
    int x = 1;
    int y = ((LINES - 5) / 2) + 2 + ((LINES % 2 == 0) ? 1 : 0);
    int w = ((COLS / 2) - 2 + ((COLS % 2 != 0) ? 1 : 0));
    int h = ((LINES - 4) / 2) - (LINES % 2 == 0 ? 1 : 0);
    int i = y + 2;

    attron(A_DIM);
    this->drawRect(x, y, w, h);
    attroff(A_DIM);
    attron(A_NORMAL);
    mvprintw(y, x + 1, " Score ");
    attroff(A_NORMAL);
    for (auto &it: scores) {
        mvprintw(i, x + 1, "%d - %s %s", i - (y + 1), it.first.c_str(), it.second.c_str());
        i++;
        if (i >= y + h)
            break;
    }
}

void MenuNCurses::drawBox(std::string username, int activeBox) {
    int x = (COLS / 2) + ((COLS % 2 != 0) ? 1 : 0);
    int y = ((LINES - 5) / 2) + 2 + ((LINES % 2 == 0) ? 1 : 0);
    int w = (COLS / 2) - 2;
    int h = 2;

    
    attron((activeBox == 2) ? A_NORMAL : A_DIM);
    if (activeBox == 2)
        attron(COLOR_PAIR(cursesColor::Line::L_GREEN));
    this->drawRect(x, y, w, h);
    if (activeBox == 2)
        attroff(COLOR_PAIR(cursesColor::Line::L_GREEN));
    attroff((activeBox == 2) ? A_NORMAL : A_DIM);
    attron((activeBox == 2) ? A_STANDOUT : A_NORMAL);
    mvprintw(y, x + 1, " Enter pseudo ");
    attroff((activeBox == 2) ? A_STANDOUT : A_NORMAL);

    for (int i = x + 1; i < (x + w); i++)
        mvaddch(y + 1, i, ' ');
    mvprintw(y + 1, x + (w / 2) - username.size() / 2, username.c_str());
}

void MenuNCurses::drawBox(int activeBox) {
    int x = (COLS / 2) + ((COLS % 2 != 0) ? 1 : 0);
    int y = ((LINES - 5) / 2) + 2 + ((LINES % 2 == 0) ? 1 : 0) + 3;
    int w = (COLS / 2) - 2;
    int h = ((LINES - 4) / 2) - (LINES % 2 == 0 ? 1 : 0) - 3;

    attron(A_STANDOUT);
    if (activeBox == 3)
        attron(COLOR_PAIR(cursesColor::Text::T_GREEN));
    mvprintw(y + (h / 2), x + (w / 2) - 3, " PLAY ");
    if (activeBox == 3)
        attroff(COLOR_PAIR(cursesColor::Text::T_GREEN));
    attroff(A_STANDOUT);
}

void MenuNCurses::display(const MenuInfo& info) {
    this->drawHolder();
    this->drawBox(info.getGraphList(), LIBS, info.getGraphIdx(), info.getActiveBoxIdx());
    this->drawBox(info.getGameList(), GAMES, info.getGameIdx(), info.getActiveBoxIdx());
    this->drawBox(info.getGameScores());
    this->drawBox(info.getActiveBoxIdx());
    this->drawBox(info.getUserName(), info.getActiveBoxIdx());
}