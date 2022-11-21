/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_LIBSFML_HPP
#define OOP_ARCADE_2019_LIBSFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "IDisplayModule.hpp"
#include "MenuSfml.hpp"

class LibSfml: public IDisplayModule {
    public:
    explicit LibSfml();
    ~LibSfml() override;
    bool isOpen() const  override;
    virtual void initWindow() override ;
    virtual void destroyWindow() override ;
    KeyBind inputListener() const;
    KeyBind eventListener() override;
    void drawEntity(const Entity &ent_1) override;
    void oneCycleDisplay()const override ;
    void oneCycleClear() override ;
    void displayMenu(const MenuInfo &menuInfo) override ;

    sf::Vector2f getVelocity(sf::Vector2f pos, sf::Vector2f dest, float speed) const;

    protected:
    private:
    std::string _name;
    sf::RenderWindow *_window;
    sf::Sprite *_player_1;
    sf::Sprite *_player_2;
    sf::Sprite *_player_3;
    sf::Sprite *_wall_1;
    sf::Sprite *_wall_2;
    sf::Sprite *_wall_3;
    sf::Sprite *_floor;
    sf::Sprite *_enemy_1;
    sf::Sprite *_enemy_2;
    sf::Sprite *_enemy_3;
    sf::Sprite *_bonus_1;
    sf::Sprite *_bonus_2;
    sf::Sprite *_bonus_3;
    sf::Sprite *_bullet;
    sf::Sprite *_error;

    MenuSfml menu;

    sf::Sprite *createSprite(const std::string& path, float x, float y);
};

#endif //OOP_ARCADE_2019_LIBSFML_HPP
