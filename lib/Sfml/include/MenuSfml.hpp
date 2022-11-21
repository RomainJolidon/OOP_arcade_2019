/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_MENUSFML_HPP
#define OOP_ARCADE_2019_MENUSFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <unordered_map>
#include <list>

class MenuSfml {
    public:
    MenuSfml();
    void displayMenu(sf::RenderWindow *);
    void createGraphicSelectionList(const std::vector<std::string>& graphicList);
    void createGameSelectionList(const std::vector<std::string>& gameList);
    void updateActivity(int activBoxIdx, int graphicIdx, int gameIdx);
    void updateSelectedGraphic(int idx);
    void updateSelectedGame(int idx);
    void updateUserName(const std::string& newName);
    void updateScores(const std::vector<std::pair<std::string, std::string>>& scores);
    bool isScoresUpToDate(const std::vector<std::pair<std::string, std::string>>& scores) const;
    long unsigned int getGraphicSelectionSize() const;
    long unsigned int getGameSelectionSize() const;
    ~MenuSfml();

    protected:
    private:
    std::vector<sf::RectangleShape *> _boxes;
    std::vector<sf::RectangleShape *> _graphicSelectionList;
    std::vector<sf::RectangleShape *> _gameSelectionList;
    std::vector<sf::Text *> _graphicNameList;
    std::vector<sf::Text *> _gameNameList;
    std::vector<sf::Text *> _texts;
    sf::Text *_userName;
    std::vector<std::pair<sf::Text *, sf::Text *>> _scoreMap;
    std::vector<sf::Text *> _scoreOrder;

    sf::RectangleShape *createRectangleShape(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
    sf::Text *createText(const std::string& fontPath, const std::string& str, sf::Vector2f pos, int size);

};

#endif //OOP_ARCADE_2019_MENUSFML_HPP
