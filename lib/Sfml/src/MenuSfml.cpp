/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include <iostream>
#include "../include/MenuSfml.hpp"

MenuSfml::MenuSfml()
{
    float y = 620;
    _boxes.push_back(createRectangleShape({10, 10}, {940, 530}, sf::Color(51, 143, 255, 255)));
    _boxes.push_back(createRectangleShape({960, 10}, {940, 530}, sf::Color(51, 143, 255, 255)));
    _boxes.push_back(createRectangleShape({960, 600}, {940, 130}, sf::Color(51, 143, 255, 255)));
    _boxes.push_back(createRectangleShape({1100, 850}, {600, 100}, sf::Color(51, 143, 255, 255)));
    _boxes.push_back(createRectangleShape({10, 550}, {940, 530}, sf::Color(51, 143, 255, 255)));

    _texts.push_back(createText("assets/font/arcade.ttf", "Graphic Selection", {470, 30}, 30));
    _texts.push_back(createText("assets/font/arcade.ttf", "Game Selection", {1430, 30}, 30));
    _texts.push_back(createText("assets/font/arcade.ttf", "Game Score", {470, 570}, 30));
    _texts.push_back(createText("assets/font/arcade.ttf", "Player", {1430, 620}, 30));
    _texts.push_back(createText("assets/font/arcade.ttf", "Play", {1400, 890}, 30));

    _userName = createText("assets/font/arcade.ttf", "USER", {1050, 690}, 50);

    for (int i = 1; i <= 5; i++) {
        _scoreOrder.push_back(createText("assets/font/arcade.ttf", std::to_string(i), {50, y}, 50));
        y += 50;
    }
};

MenuSfml::~MenuSfml()
= default;

sf::RectangleShape *MenuSfml::createRectangleShape(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
    sf::RectangleShape *rect = new sf::RectangleShape();

    rect->setSize(size);

    rect->setPosition(pos);
    rect->setFillColor(color);
    //rect->setFillColor(sf::Color(51, 143, 255, 255));
    rect->setOutlineColor(sf::Color::Blue);
    rect->setOutlineThickness(3);
    return (rect);
}

sf::Text *MenuSfml::createText(const std::string& fontPath, const std::string& str, sf::Vector2f pos, int size)
{
    sf::Text *text = new sf::Text();
    sf::Font *font = new sf::Font();
    sf::FloatRect textRect;

    font->loadFromFile(fontPath);

    text->setPosition(pos);
    text->setString(str);
    text->setFont(*font);
    text->setFillColor(sf::Color::White);
    text->setOutlineColor(sf::Color::Black);
    text->setOutlineThickness(3);
    text->setCharacterSize(size);

    textRect = text->getLocalBounds();
    text->setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);

    return (text);
}

void MenuSfml::displayMenu(sf::RenderWindow *window)
{
    int count = _scoreMap.size();
    for (auto &box: _boxes) {
        window->draw(*box);
    }
    for (auto &selection: _graphicSelectionList) {
        window->draw(*selection);
    }
    for (auto &selection: _gameSelectionList) {
        window->draw(*selection);
    }
    for (auto &text: _texts) {
        window->draw(*text);
    }
    for (auto &text: _graphicNameList) {
        window->draw(*text);
    }
    for (auto &text: _gameNameList) {
        window->draw(*text);
    }
    window->draw(*_userName);
    for (auto& order: _scoreOrder) {
        if (count == 0)
            break;
        window->draw(*order);
        count--;
    }
    for (auto &score: _scoreMap) {
        window->draw(*score.first);
        window->draw(*score.second);
    }
}

void MenuSfml::createGraphicSelectionList(const std::vector<std::string>& graphicList)
{
    sf::Vector2f pos = {20, 70};
    float offset = 10;
    sf::Vector2f boxSize = {920, (460 / graphicList.size()) - offset};

    for (auto elem: graphicList) {
        _graphicSelectionList.push_back(
            createRectangleShape(pos, boxSize, sf::Color(239, 77, 77, 250)));
        _graphicNameList.push_back(createText("assets/font/arcade-italic.ttf", elem,
            {pos.x + (boxSize.x / 2), pos.y + (boxSize.y / 2)}, 30));
        pos.y += boxSize.y + offset;
    }
}

long unsigned int MenuSfml::getGraphicSelectionSize() const
{
    return (_graphicSelectionList.size());
}

long unsigned int MenuSfml::getGameSelectionSize() const
{
    return (_gameSelectionList.size());
}

void MenuSfml::createGameSelectionList(const std::vector<std::string> &gameList)
{
    sf::Vector2f pos = {970, 70};
    float offset = 10;
    sf::Vector2f boxSize = {920, (460 / gameList.size()) - offset};

    for (auto elem: gameList) {
        _gameSelectionList.push_back(
            createRectangleShape(pos, boxSize, sf::Color(239, 77, 77, 250)));
        _gameNameList.push_back(createText("assets/font/arcade-italic.ttf", elem,
            {pos.x + (boxSize.x / 2), pos.y + (boxSize.y / 2)}, 30));
        pos.y += boxSize.y + offset;
    }
}

void MenuSfml::updateSelectedGraphic(int idx)
{
    int count = 0;

    if (_graphicSelectionList.empty())
        return;
    for (auto it = _graphicSelectionList.begin(); it != _graphicSelectionList.end(); it++) {
        if (count == idx)
            (*it)->setFillColor(sf::Color::Red);
        else
            (*it)->setFillColor(sf::Color(239, 77, 77, 250));
        count++;
    }
}

void MenuSfml::updateSelectedGame(int idx)
{
    int count = 0;

    if (_gameSelectionList.empty())
        return;
    for (auto it = _gameSelectionList.begin(); it != _gameSelectionList.end(); it++) {
        if (count == idx)
            (*it)->setFillColor(sf::Color::Red);
        else
            (*it)->setFillColor(sf::Color(239, 77, 77, 250));
        count++;
    }
}

void MenuSfml::updateActivity(int activBoxIdx, int graphicIdx, int gameIdx)
{
    static bool firstTime = true;
    int count = 0;
    std::vector<sf::RectangleShape *>::iterator toSelect = _boxes.begin();

    for (auto it = _boxes.begin(); it != _boxes.end(); it++) {
        if (count == activBoxIdx)
            toSelect = it;
        else
            (*it)->setFillColor(sf::Color(51, 143, 255, 255));
        count++;
    }
    (*toSelect)->setFillColor(sf::Color::Blue);
    if (firstTime) {
        updateSelectedGraphic(graphicIdx);
        updateSelectedGame(gameIdx);
        firstTime = false;
        return;
    }
    if (activBoxIdx == 0) {
        updateSelectedGraphic(graphicIdx);
    } else if (activBoxIdx == 1)
        updateSelectedGame(gameIdx);
}

void MenuSfml::updateUserName(const std::string &newName)
{
    _userName->setString(newName);
}

void MenuSfml::updateScores(const std::vector<std::pair<std::string, std::string>>& scores)
{
    int count = scores.size();
    float y = 620;
    if (isScoresUpToDate(scores)) {
        return;
    }

    _scoreMap.clear();
    if (count > 5)
        count = 5;
    for (auto &it: scores) {
        _scoreMap.push_back(std::make_pair(createText("assets/font/arcade.ttf", it.first, {470, y}, 50),
            createText("assets/font/arcade.ttf", it.second, {850, y}, 50)));
        y += 50;
        count--;
        if (count == 0)
            break;
    }
}

bool MenuSfml::isScoresUpToDate(const std::vector<std::pair<std::string, std::string>>& scores) const
{
    bool valid = true;
    int count = 0;
    int value = 0;

    if (scores.size() <= 5) {
        if (_scoreMap.size() != scores.size())
            return (false);
    }
    for (auto &self: _scoreMap) {
        valid = true;
        count = 0;
        for (auto &other: scores) {
            if (count == value) {
                if (self.first->getString().toAnsiString() != other.first || self.second->getString().toAnsiString() != other.second) {
                    valid = false;
                }
                break;
            }
            count++;
        }
        if (!valid)
            return (false);
        value++;
    }
    return !(_scoreMap.empty() && !scores.empty());
}
