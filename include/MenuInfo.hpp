/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_MENUINFO_HPP
#define OOP_ARCADE_2019_MENUINFO_HPP

#include <vector>
#include <unordered_map>
#include <string>

class MenuInfo {
    public:
    MenuInfo();
    ~MenuInfo();
    std::vector<std::string> getGraphList() const;
    void setGraphList(std::vector<std::string> graphList);
    std::vector<std::string> getGameList() const;
    void setGameList(std::vector<std::string> gameList);
    std::vector<std::pair<std::string, std::string>> getGameScores() const;
    void setGameScores(const std::vector<std::pair<std::string, std::string>>& scores);
    int getGraphIdx() const;
    void setGraphIdx(int graphIdx);
    int getGameIdx() const;
    void setGameIdx(int gameIdx);
    int getActiveBoxIdx() const;
    void setActiveBoxIdx(int activeBoxIdx);
    std::string getUserName() const;
    void setUserName(std::basic_string<char> userName);
    const std::string& getGameName() const ;
    protected:
    private:
    std::vector<std::string> _graphList;
    std::vector<std::string> _gameList;
    std::vector<std::pair<std::string, std::string>> _gameScores;
    std::string _userName;
    int _graphIdx;
    int _gameIdx;
    int _activeBoxIdx;
};

#endif //OOP_ARCADE_2019_MENUINFO_HPP
