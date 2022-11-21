/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "Core.hpp"

Core::Core() :
    _scene(COREMENU), _libGraph(nullptr), _libGame(nullptr)
{}

Core::~Core()
= default;

void Core::loadGraphicLibs()
{
    DIR *dir = nullptr;

    dir = opendir("./lib");
    if (!dir)
        throw Error::CoreError("Failed to load Graphical libraries: path './lib' not found.");
    try {
        _graphicMap = Parser::readDirLib<IDisplayModule>(dir, "./lib/", ".so");
    } catch (const Error::CoreError& e) {
        throw e;
    }
    Parser::closeDir(dir);
}

void Core::loadGameLibs()
{
    DIR *dir = nullptr;

    dir = Parser::openDir("./games");
    if (!dir)
        throw Error::CoreError("Failed to load Game libraries: path './games' not found.");
    try {
        _gameMap = Parser::readDirLib<IGameModule>(dir, "./games/", ".so");
    } catch (const Error::CoreError& e) {
        throw e;
    }
    Parser::closeDir(dir);
}

void Core::loadGamesSaves()
{
    DIR *dir = nullptr;
    std::string name;

    if (!Parser::isDirExists("./games/saves")) {
        Parser::createDir("./games/saves", 0777);
    }
    dir = Parser::openDir("./games/saves");
    if (!dir)
        throw Error::CoreError("Failed to load Game save: path './games/saves' not found.");
    while ((name = Parser::readDirOnce(dir, ".txt")) != "end") {
        if (name.empty())
            continue;
        try {
            loadFileSave(Parser::getLibPath(name, "./games/saves/"));
        } catch (const Error::CoreError &e) {
            throw e;
        }
    }
    Parser::closeDir(dir);
}


bool Core::sortScores(std::pair<std::string, std::string> first, std::pair<std::string, std::string> second)
{
    return (std::atoi(first.second.c_str()) > std::atoi(second.second.c_str()));
}

void Core::loadFileSave(const std::string &filepath)
{
    std::ifstream fd;
    std::string line;


    fd.open(filepath);
    if (!fd.is_open()) {
        _savesMap[filepath].clear();
        return;
    }
    while (std::getline(fd, line)) {
        if (line.find('=') == std::string::npos)
            throw Error::CoreError("Failed to load save in file: " + filepath + ": invalid line found: " += line + ".");
        _savesMap[filepath].push_back(std::make_pair(line.substr(0, line.find('=')), line.substr(line.find('=') + 1)));
    }
    fd.close();
    std::sort(_savesMap[filepath].begin(), _savesMap[filepath].end(), sortScores);
}

std::unordered_map<std::string, DLLoader<IDisplayModule> *> Core::getGraphicMap() const
{
    return _graphicMap;
}

std::unordered_map<std::string, DLLoader<IGameModule> *> Core::getGameMap() const
{
    return _gameMap;
}

void Core::CoreLoop(MenuInfo *menuInfo)
{
    std::chrono::time_point<std::chrono::steady_clock> clock = std::chrono::steady_clock::now();
    unsigned long long int elapsedTime = 0;
    KeyBind key = KeyBind ::NONE;
    std::string libName = menuInfo->getGraphList()[menuInfo->getGraphIdx()];
    std::string gameName = menuInfo->getGameList()[menuInfo->getGameIdx()];

    if (_libGame)
        delete  _libGame;
    try {
        _libGraph = _graphicMap[libName]->getInstance("entryPoint");
        _libGame = _gameMap[gameName]->getInstance("entryPoint");
        _graphicIt = _graphicMap.find(libName);
        _gameIt = _gameMap.find(gameName);
    } catch(const std::exception &e) {
        e.what();
        return;
    }

    while (_libGraph->isOpen() && (_scene == GAME || _scene == PAUSED)) {
        elapsedTime = static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - clock).count());
        if (elapsedTime > 50) {
            key = _libGraph->eventListener();
            HandleLibrarySwitchEvts(key);

            _libGraph->oneCycleClear();
            for (auto &it : _libGame->getEntities())
                _libGraph->drawEntity(*it);
            if (_scene != PAUSED) {
                _libGame->receiveEvent(key);

                if (!_libGame->oneCycleLoop()) {
                    writeScoresInFile(gameName, menuInfo, _libGame->getScore());
                    break;
                }
            }
            _libGraph->oneCycleDisplay();
            clock = std::chrono::steady_clock::now();
        }
    }
    delete _libGame;
    _libGame = nullptr;
    _scene = COREMENU;
}

void Core::writeScoresInFile(const std::string& gameName, MenuInfo *menuInfo, int score) const
{
    std::ofstream myfile;
    std::string name = gameName.substr(gameName.find_last_of('/') + 1,   gameName.find_last_of('.') - (gameName.find_last_of('/') + 1));
    myfile.open("./games/saves/" + name + ".txt", std::ios_base::app);
    myfile << menuInfo->getUserName() << "=" << score << std::endl;
    myfile.close();
}


void Core::StartCoreMenu(const std::string &libName)
{
    MenuInfo menuInfo;
    std::vector<std::string> graphList;
    std::vector<std::string> gameList;

    try {
        loadGraphicLibs();
        loadGameLibs();
        loadGamesSaves();
    } catch (const Error::CoreError& e) {
        throw e;
    }
    try {
        if (!_graphicMap.empty())
           _libGraph = _graphicMap[libName]->getInstance("entryPoint");
        else
            throw Error::CoreError("Failed to find graphical library");
    } catch(const std::exception &e) {
        throw e;
    }
    for (auto it = _graphicMap.begin(); it != _graphicMap.end(); it++) {
        if ((*it).first == libName)
            menuInfo.setGraphIdx(std::distance(_graphicMap.begin(), it));
        graphList.push_back((*it).first);
    }
    if (_gameMap.empty())
        throw Error::CoreError("No game found: play gameplay possible");
    for (auto & it : _gameMap)
        gameList.push_back(it.first);
    menuInfo.setGraphList(graphList);
    menuInfo.setGameList(gameList);

        updateScoreMenu(&menuInfo, menuInfo.getGameName());
    while (_libGraph->isOpen()) {
        _libGraph->oneCycleClear();
        _libGraph->displayMenu(menuInfo);
        HandleCoreMenuEvts(&menuInfo, _libGraph->eventListener());
        if (_scene == GAME) {
            delete _libGraph;
            CoreLoop(&menuInfo);
        }
        _libGraph->oneCycleDisplay();
    }
    delete _libGraph;
    closeLibMaps(libName);
}

void Core::updateScoreMenu(MenuInfo *menuInfo, const std::string &gameName)
{
    std::string name = "./games/saves/" + gameName.substr(gameName.find_last_of('/') + 1,   gameName.find_last_of('.') - (gameName.find_last_of('/') + 1)) + ".txt";

    menuInfo->setGameScores(_savesMap[name]);
}

void Core::HandleCoreMenuEvts(MenuInfo *menuInfo, KeyBind key)
{
    switch (key) {
    case ARROWLEFT:
        menuInfo->setActiveBoxIdx((((menuInfo->getActiveBoxIdx() - 1) % 4) < 0 ?
            ((menuInfo->getActiveBoxIdx() - 1) % 4) + 4 :
            ((menuInfo->getActiveBoxIdx() - 1) % 4)));
        break;
    case ARROWRIGHT:
        menuInfo->setActiveBoxIdx((menuInfo->getActiveBoxIdx() + 1) % 4);
        break;
    case ARROWUP:
        if (menuInfo->getActiveBoxIdx() == 0) {
            if (menuInfo->getGraphIdx() - 1 < 0)
                menuInfo->setGraphIdx(menuInfo->getGraphList().size() - 1);
            else
                menuInfo->setGraphIdx((menuInfo->getGraphIdx() - 1) %
                menuInfo->getGraphList().size());
        } else if (menuInfo->getActiveBoxIdx() == 1) {
            if (menuInfo->getGameIdx() - 1 < 0)
                menuInfo->setGameIdx(menuInfo->getGameList().size() - 1);
            else
                menuInfo->setGameIdx(
                (menuInfo->getGameIdx() - 1) % menuInfo->getGameList().size());
            updateScoreMenu(menuInfo, menuInfo->getGameName());
        }
        break;
    case ARROWDOWN:
        if (menuInfo->getActiveBoxIdx() == 0)
            menuInfo->setGraphIdx((menuInfo->getGraphIdx() + 1) %
                menuInfo->getGraphList().size());
        else if (menuInfo->getActiveBoxIdx() == 1) {
            menuInfo->setGameIdx(
                (menuInfo->getGameIdx() + 1) % menuInfo->getGameList().size());
            updateScoreMenu(menuInfo, menuInfo->getGameName());
        }
        break;
    case ENTER:
        if (menuInfo->getActiveBoxIdx() == 3) {
            _scene = GAME;
        }
        break;
    case RETURN:
        if (!menuInfo->getUserName().empty() &&
            menuInfo->getActiveBoxIdx() == 2)
            menuInfo->setUserName(menuInfo->getUserName().substr(0,
                menuInfo->getUserName().size() - 1));
        break;
    default:
        break;
    }

    if (menuInfo->getActiveBoxIdx() == 2) {
        for (int i = KeyBind::A; i != KeyBind::Z; i++) {
            if (key == static_cast<KeyBind >(i)) {
                menuInfo->setUserName(menuInfo->getUserName() += static_cast<char>('A' + (i - KeyBind::A)));
            }
        }
    }
}

void Core::HandleLibrarySwitchEvts(KeyBind key)
{
    switch (key) {
    case PREV_LIB:
        key = F1;
        break;
    case NEXT_LIB:
        key = F2;
        break;
    case PREV_GAME:
        key = F3;
        break;
    case NEXT_GAME:
        key = F4;
        break;
    case RESTART:
        key = F5;
        break;
    case MENU:
        key = F6;
        break;
    case PAUSE:
        key = F7;
        break;
    default:
        break;
    }
    switch (key) {
    case F1:
        if (_scene == GAME || _scene == PAUSED) {
            if (_graphicIt == _graphicMap.begin()) {
                _graphicIt = std::next(_graphicMap.begin(),
                    _graphicMap.size() - 1);
            } else {
                //_graphicIt = _graphicMap.begin();
                _graphicIt = std::next(_graphicMap.begin(), std::distance(_graphicMap.begin(), _graphicIt) - 1);
            }
            delete _libGraph;
            _libGraph = (*_graphicIt).second->getInstance("entryPoint");
        }
        break;
    case F2:
        if (_scene == GAME || _scene == PAUSED) {
            if (_graphicIt ==
                std::next(_graphicMap.begin(), _graphicMap.size() - 1)) {
                _graphicIt = _graphicMap.begin();
            } else {
                _graphicIt = std::next(_graphicIt, 1);
            }
            delete _libGraph;
            _libGraph = (*_graphicIt).second->getInstance("entryPoint");
        }
        break;
    case F3:
        if (_scene == GAME || _scene == PAUSED) {
            if (_gameIt == _gameMap.begin()) {
                _gameIt = std::next(_gameMap.begin(), _gameMap.size() - 1);
            } else {
                //_gameIt = _gameMap.begin();
                _gameIt = std::next(_gameMap.begin(), std::distance(_gameMap.begin(), _gameIt) - 1);
            }
            delete _libGame;
            _libGame = (*_gameIt).second->getInstance("entryPoint");
            _scene = GAME;
        }
        break;
    case F4:
        if (_scene == GAME || _scene == PAUSED) {
            if (_gameIt == std::next(_gameMap.begin(), _gameMap.size() - 1)) {
                _gameIt = _gameMap.begin();
            } else {
                _gameIt = std::next(_gameIt, 1);
            }
            delete _libGame;
            _libGame = (*_gameIt).second->getInstance("entryPoint");
            _scene = GAME;
        }
        break;
    case F5:
        if (_scene == GAME || _scene == PAUSED) {
            delete _libGame;
            _libGame = (*_gameIt).second->getInstance("entryPoint");
            _scene = GAME;
        }
        break;
    case F6:
        if (_scene != COREMENU)
            _scene = COREMENU;
        break;
    case F7:
        if (_scene != COREMENU) {
            if (_scene != PAUSED)
                _scene = PAUSED;
            else
                _scene = GAME;
        }
        break;
    default:
        break;
    }
}

void Core::closeLibMaps(const std::string& first)
{
    std::unordered_map<std::string, DLLoader<IDisplayModule> *>::const_iterator it;
    delete _graphicMap[first];
    for (it = _graphicMap.begin(); it != _graphicMap.end(); it++) {
        if (it->first != first) {
            std::cout << it->first << std::endl;
            //fixme segfault si delete les autres elements de la map
        }
    }
}