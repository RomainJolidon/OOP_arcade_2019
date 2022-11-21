/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_CORE_HPP
#define OOP_ARCADE_2019_CORE_HPP

#include <unordered_map>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include "MenuInfo.hpp"
#include "DLLoader.hpp"
#include "Parser.hpp"
#include "Error.hpp"

enum Scene {
   COREMENU,
   GAME,
   PAUSED,
   CLOSE,
};

class Core {
    public:

    Core();
    ~Core();
    void loadGraphicLibs();
    void loadGameLibs();
    void loadGamesSaves();
    void loadFileSave(const std::string& filepath);
    std::unordered_map<std::string, DLLoader<IDisplayModule> *> getGraphicMap() const;
    std::unordered_map<std::string, DLLoader<IGameModule> *> getGameMap() const;
    void CoreLoop(MenuInfo *menuInfo);
    void StartCoreMenu(const std::string& libName);
    void HandleCoreMenuEvts(MenuInfo *menuInfo, KeyBind key);
    void HandleLibrarySwitchEvts(KeyBind key);
    void closeLibMaps(const std::string& first);
    void writeScoresInFile(const std::string& gameName, MenuInfo *menuInfo, int score) const;
    void updateScoreMenu(MenuInfo *menuInfo, const std::string& gameName);
    protected:


    private:
    std::unordered_map<std::string, DLLoader<IDisplayModule> *> _graphicMap;
    std::unordered_map<std::string, DLLoader<IGameModule> *> _gameMap;

    Scene _scene;
    IDisplayModule *_libGraph;
    IGameModule *_libGame;
    std::unordered_map<std::string, DLLoader<IDisplayModule> *>::iterator _graphicIt;
    std::unordered_map<std::string, DLLoader<IGameModule> *>::iterator  _gameIt;
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> _savesMap;

    static bool sortScores(std::pair<std::string, std::string> first, std::pair<std::string, std::string> second);
};

#endif //OOP_ARCADE_2019_CORE_HPP
