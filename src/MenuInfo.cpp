/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#include "MenuInfo.hpp"

#include <utility>

MenuInfo::MenuInfo() : _userName(""), _graphIdx(0), _gameIdx(0), _activeBoxIdx(0)
{}

MenuInfo::~MenuInfo()
= default;

std::vector<std::string> MenuInfo::getGraphList() const
{
    return _graphList;
}

std::vector<std::string> MenuInfo::getGameList() const
{
    return _gameList;
}

std::vector<std::pair<std::string, std::string>> MenuInfo::getGameScores() const
{
    return _gameScores;
}

int MenuInfo::getGraphIdx() const
{
    return _graphIdx;
}

int MenuInfo::getGameIdx() const
{
    return _gameIdx;
}

int MenuInfo::getActiveBoxIdx() const
{
    return _activeBoxIdx;
}

void MenuInfo::setGraphList(std::vector<std::string> graphList)
{
    _graphList = std::move(graphList);
}

void MenuInfo::setGameList(std::vector<std::string> gameList)
{
    _gameList = std::move(gameList);
}

void MenuInfo::setGameScores(const std::vector<std::pair<std::string, std::string>>& scores)
{
    _gameScores.clear();
    for (auto &it: scores) {
        _gameScores.push_back(it);
    }
}

void MenuInfo::setGraphIdx(int graphIdx)
{
    _graphIdx = graphIdx;
}

void MenuInfo::setGameIdx(int gameIdx)
{
    _gameIdx = gameIdx;
}

void MenuInfo::setActiveBoxIdx(int activeBoxIdx)
{
    _activeBoxIdx = activeBoxIdx;
}

std::string MenuInfo::getUserName() const
{
    return _userName;
}

void MenuInfo::setUserName(std::basic_string<char> userName)
{
    _userName = std::move(userName);
}

const std::string &MenuInfo::getGameName() const
{
    return (_gameList.at(_gameIdx));
}
