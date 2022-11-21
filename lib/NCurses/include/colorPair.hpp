/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** color_pair
*/

#ifndef COLOR_PAIR_HPP_
#define COLOR_PAIR_HPP_

namespace cursesColor {
    enum Text: short {
        T_BLACK = 0,
        T_RED = 1,
        T_GREEN = 2,
        T_YELLOW = 3,
        T_BLUE = 4,
        T_MAGENTA = 5,
        T_CYAN = 6,
        T_WHITE = 7
    };
    enum Line: short {
        L_BLACK = 8,
        L_RED = 9,
        L_GREEN = 10,
        L_YELLOW = 11,
        L_BLUE = 12,
        L_MAGENTA = 13,
        L_CYAN = 14,
        L_WHITE = 15
    };
    enum Entity: short {
        PLAYER_1 = 16,
        ENEMY_1 = 17,
        ENEMY_2 = 18,
        ENEMY_3 = 19,
        WALL_1 = 20,
        FLOOR = 21,
        BONUS_1 = 22,
        BONUS_2 = 23,
        BONUS_3 = 24,
        PROJECTILE = 25,
        BULLET = 26,
        WALL_2 = 27,
        WALL_3 = 28,
        WALL_4 = 29,
        SNAKE_2 = 30,
        PLAYER_2 = 31,
        PLAYER_3 = 32,
        BACKGROUND = 33,
        GAME_WON = 34,
        GAME_LOST = 35,
        TITLEMENU = 36,
        TITLEGAME = 37,
        ERROR = 38,
        MAP = 39
    };
};

#endif /* !COLOR_PAIR_HPP_ */