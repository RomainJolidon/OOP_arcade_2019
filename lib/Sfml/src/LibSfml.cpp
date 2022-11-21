/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/LibSfml.hpp"

LibSfml::LibSfml():
_name("LibSfml"), _window(nullptr),
_player_1(createSprite("assets/PLAYER_1.png", 0, 0)),
_player_2(createSprite("assets/PLAYER_2.png", 0, 0)),
_player_3(createSprite("assets/PLAYER_3.png", 0, 0)),
_wall_1(createSprite("assets/WALL_1.png", 0, 0)),
_wall_2(createSprite("assets/WALL_2.png", 0, 0)),
_wall_3(createSprite("assets/WALL_3.png", 0, 0)),
_floor(createSprite("assets/floor.png", 0, 0)),
_enemy_1(createSprite("assets/ENEMY_1.png", 0, 0)),
_enemy_2(createSprite("assets/ENEMY_2.png", 0, 0)),
_enemy_3(createSprite("assets/ENEMY_3.png", 0, 0)),
_bonus_1(createSprite("assets/BONUS_1.png", 0, 0)),
_bonus_2(createSprite("assets/BONUS_2.png", 0, 0)),
_bonus_3(createSprite("assets/BONUS_3.png", 0, 0)),
_bullet(createSprite("assets/bullet.png", 0, 0)),
_error(createSprite("assets/error.png", 0, 0))
{
    sf::VideoMode mode = sf::VideoMode(1920, 1080, 32);
    _window = new sf::RenderWindow(mode, "SFML");

     _window->setFramerateLimit(30);
}

LibSfml::~LibSfml()
{
    if (_window->isOpen())
        _window->close();
}

void LibSfml::initWindow()
{
    if (_window->isOpen())
        return;
    sf::VideoMode mode = sf::VideoMode(1920, 1080, 32);
    _window = new sf::RenderWindow(mode, "SFML");

    _window->setFramerateLimit(30);
}

void LibSfml::destroyWindow()
{
    if (_window->isOpen())
        _window->close();
    _window = nullptr;
}

KeyBind LibSfml::inputListener() const
{
    int charKeys[] = {0, 26};

    for (int i = charKeys[0]; i <= charKeys[1]; i++) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
            return (static_cast<KeyBind >(i + 6));
    }
    return (KeyBind::NONE);
}

void LibSfml::oneCycleDisplay() const
{
    if (_window->isOpen())
        _window->display();
}

void LibSfml::oneCycleClear()
{
    if (_window->isOpen())
        _window->clear(sf::Color::Black);
}

KeyBind LibSfml::eventListener()
{
    sf::Event event;
    int charKeys[] = {0, 26};

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Down)
                return (KeyBind::ARROWDOWN);
            if (event.key.code == sf::Keyboard::Key::Up)
                return (KeyBind::ARROWUP);
            if (event.key.code == sf::Keyboard::Key::Left)
                return (KeyBind::ARROWLEFT);
            if (event.key.code == sf::Keyboard::Key::Right)
                return (KeyBind::ARROWRIGHT);
            if (event.key.code == sf::Keyboard::Key::Return)
                return (KeyBind::ENTER);
            if (event.key.code == sf::Keyboard::Key::BackSpace)
                return (KeyBind::RETURN);
            if (event.key.code == sf::Keyboard::Key::F1)
                return (KeyBind::F1);
            if (event.key.code == sf::Keyboard::Key::F2)
                return (KeyBind::F2);
            if (event.key.code == sf::Keyboard::Key::F3)
                return (KeyBind::F3);
            if (event.key.code == sf::Keyboard::Key::F4)
                return (KeyBind::F4);
            if (event.key.code == sf::Keyboard::Key::F5)
                return (KeyBind::F5);
            if (event.key.code == sf::Keyboard::Key::F6)
                return (KeyBind::F6);
            if (event.key.code == sf::Keyboard::Key::F6)
                return (KeyBind::F6);
            if (event.key.code == sf::Keyboard::Key::F7)
                return (KeyBind::F7);
            for (int i = charKeys[0]; i <= charKeys[1]; i++) {
                if (event.key.code == static_cast<sf::Keyboard::Key>(i))
                    return (static_cast<KeyBind >(i + 6));
            }
        }
    }
    return (KeyBind::NONE);
}

bool LibSfml::isOpen() const
{
    if (_window == nullptr)
        return (false);
    return (_window->isOpen());
}

void LibSfml::drawEntity(const Entity &ent_1)
{
    float x = ent_1.getPosX() * 32;
    float y = ent_1.getPosY() * 32;
    switch (ent_1.getType()) {
    case PLAYER_1:
        _player_1->setPosition({x, y});
        _window->draw(*_player_1);
        break;
    case PLAYER_2:
        _player_2->setPosition({x, y});
        _window->draw(*_player_2);
        break;
    case PLAYER_3:
        _player_3->setPosition({x, y});
        _window->draw(*_player_3);
        break;
    case ENEMY_1:
        _enemy_1->setPosition({x, y});
        _window->draw(*_enemy_1);
        break;
    case ENEMY_2:
        _enemy_2->setPosition({x, y});
        _window->draw(*_enemy_2);
        break;
    case ENEMY_3:
        _enemy_3->setPosition({x, y});
        _window->draw(*_enemy_3);
        break;
    case WALL_1:
        _wall_1->setPosition({x, y});
        _window->draw(*_wall_1);
        break;
    case WALL_2:
        _wall_2->setPosition({x, y});
        _window->draw(*_wall_2);
        break;
    case WALL_3:
        _wall_3->setPosition({x, y});
        _window->draw(*_wall_3);
        break;
    case FLOOR:
        _floor->setPosition({x, y});
        _window->draw(*_floor);
        break;
    case BONUS_1:
        _bonus_1->setPosition({x, y});
        _window->draw(*_bonus_1);
        break;
    case BONUS_2:
        _bonus_2->setPosition({x, y});
        _window->draw(*_bonus_2);
        break;
    case BONUS_3:
        _bonus_3->setPosition({x, y});
        _window->draw(*_bonus_3);
        break;
    case BULLET:
        _bullet->setPosition({x, y});
        _window->draw(*_bullet);
        break;
    default:
        _error->setPosition({x, y});
        _window->draw(*_error);
        break;
    }
}

sf::Sprite *LibSfml::createSprite(const std::string &path, float x, float y)
{
    sf::Sprite *sprite = new sf::Sprite();
    sf::Texture *texture = new sf::Texture();

    texture->loadFromFile(path);

    sprite->setTexture(*texture, true);
    sprite->setPosition({x, y});
    return (sprite);
}

void LibSfml::displayMenu(const MenuInfo &menuInfo)
{
    if (menuInfo.getGraphList().size() != menu.getGraphicSelectionSize())
        menu.createGraphicSelectionList(menuInfo.getGraphList());
    if (menuInfo.getGameList().size() != menu.getGameSelectionSize())
        menu.createGameSelectionList(menuInfo.getGameList());
    menu.updateScores(menuInfo.getGameScores());
    menu.updateActivity(menuInfo.getActiveBoxIdx(), menuInfo.getGraphIdx(), menuInfo.getGameIdx());
    menu.updateUserName(menuInfo.getUserName());
    menu.displayMenu(_window);
}

sf::Vector2f LibSfml::getVelocity(sf::Vector2f pos, sf::Vector2f dest, float speed) const
{
    sf::Vector2f velocity = {0, 0};

    if (dest.x * 32 > pos.x)
        velocity.x += speed;
    else if (dest.x * 32 < pos.x)
        velocity.x -= speed;

    if (dest.y * 32 > pos.y)
        velocity.y += speed;
    else if (dest.y * 32 < pos.y)
        velocity.y -= speed;
    return (velocity);
}

extern "C" IDisplayModule *entryPoint()
{
    return (new LibSfml());
}