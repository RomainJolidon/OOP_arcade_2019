/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/LibQix.hpp"

LibQix::LibQix()
: _score(0), _nbEnnemies(3)
{
    srand(time(NULL));
    initAllEntities();
}

LibQix::~LibQix()
{
}

void LibQix::initAllEntities()
{
    //Map creation
    std::list<std::string> map = Parser::parseMap("games/Qix/map/map_01", 6, 17);
    int x = 0;
    int y = Parser::getTop();
    std::pair<int, int> randPos;
    unsigned long long int enemyId;



    for (auto & line: map) {
        x = Parser::getLeft();
        for (char c: line) {
            switch (c) {
            case ' ':
                addFloor(x, y);
                break;
            case '#':
                addWall(x, y);
                break;
            case '*':
                addFloor(x, y);
                break;
            default:
                break;
            }
            x++;
        }
        y++;
    }

    initBordervector(Parser::getLeft(), Parser::getTop());

    randPos = getRandomBorderPos();
    //Player creation
    ECSEntity player = _instance.newEntity();

    _positionStorage.addComponentForEntity(player._id);
    _positionStorage.getComponentForEntity(player._id) = Position{player._id, randPos.first, randPos.second};
    _velocityStorage.addComponentForEntity(player._id);
    _velocityStorage.getComponentForEntity(player._id) = Velocity{player._id, 0, 0};
    _colliderStorage.addComponentForEntity(player._id);
    _colliderStorage.getComponentForEntity(player._id) = Collider{player._id, 1, 1};
    _typeStorage.addComponentForEntity(player._id);
    _typeStorage.getComponentForEntity(player._id) = Tag{player._id, PLAYER_1};
    _clockStorage.addComponentForEntity(player._id);
    _clockStorage.getComponentForEntity(player._id) = Clock{player._id, 0, 2};
    _pathStorage.addComponentForEntity(player._id);
    _pathStorage.getComponentForEntity(player._id) = Path{player._id, false, std::vector<std::pair<int, int>>()};
    _pathStorage.getComponentForEntity(player._id).path.emplace_back(randPos.first, randPos.second);

    _playableStorage.addComponentForEntity(player._id);
    _playableStorage.getComponentForEntity(player._id) = Playable{player._id, NONE};

    for (int i = 0; i < _nbEnnemies; i++) {
        enemyId = _instance.newEntity()._id;
        randPos = getRandomBorderPos();

        _positionStorage.addComponentForEntity(enemyId);
        _positionStorage.getComponentForEntity(enemyId) = Position{enemyId, randPos.first, randPos.second};
        _velocityStorage.addComponentForEntity(enemyId);
        _velocityStorage.getComponentForEntity(enemyId) = Velocity{enemyId, 0, 0};
        _colliderStorage.addComponentForEntity(enemyId);
        _colliderStorage.getComponentForEntity(enemyId) = Collider{player._id, 1, 1};
        _typeStorage.addComponentForEntity(enemyId);
        _typeStorage.getComponentForEntity(enemyId) = Tag{enemyId, ENEMY_1};
        _clockStorage.addComponentForEntity(enemyId);
        _clockStorage.getComponentForEntity(enemyId) = Clock{enemyId, 0, 3};
        _AIStorage.addComponentForEntity(enemyId);
        _AIStorage.getComponentForEntity(enemyId) = AI{enemyId};
    }
}

void LibQix::destroyAllEntities()
{
    _instance._entityList.clear();
    _velocityStorage.componentVector.clear();
    _velocityStorage.entityIdxToComponentIdxMap.clear();
    _positionStorage.componentVector.clear();
    _positionStorage.entityIdxToComponentIdxMap.clear();
    _colliderStorage.componentVector.clear();
    _colliderStorage.entityIdxToComponentIdxMap.clear();
    _typeStorage.componentVector.clear();
    _typeStorage.entityIdxToComponentIdxMap.clear();
    _playableStorage.componentVector.clear();
    _playableStorage.entityIdxToComponentIdxMap.clear();
    _clockStorage.componentVector.clear();
    _clockStorage.entityIdxToComponentIdxMap.clear();
    _AIStorage.componentVector.clear();
    _AIStorage.entityIdxToComponentIdxMap.clear();
    _pathStorage.componentVector.clear();
    _pathStorage.entityIdxToComponentIdxMap.clear();
    _borderVector.clear();
}

void LibQix::resetGame()
{
    destroyAllEntities();
    initAllEntities();
}

void LibQix::receiveEvent(KeyBind key)
{
    _inputSystem.update(&_playableStorage, &_pathStorage, &_velocityStorage, key);
}

const std::vector<Entity *> &LibQix::getEntities()
{
    int x;
    int y;
    TypeEntity type;
    _entities.clear();
    for (const auto& it : _instance._entityList) {
        x =_positionStorage.getComponentForEntity(it._id).x;
        y =_positionStorage.getComponentForEntity(it._id).y;
        type =_typeStorage.getComponentForEntity(it._id).type;
        _entities.push_back(new Entity(type, x, y));
    }
    return _entities;
}

bool LibQix::oneCycleLoop()
{
    _clockSystem.update(&_clockStorage);
    _AISystem.update(&_AIStorage, &_velocityStorage, &_positionStorage, _borderVector);
    if (!_collisionSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_typeStorage))
        return (false);
    _movementSystem.update(&_positionStorage, &_velocityStorage, &_clockStorage, &_typeStorage, &_pathStorage);
    _pathSystem.update(&_pathStorage, &_positionStorage, &_typeStorage);
    getSurface();
    //std::cout << "completion: " << _borderVector.size() * 100 / (2 * Parser::getHeight() + 2 * Parser::getWidth()) << std::endl;
    if (_borderVector.size() * 100 / (2 * Parser::getHeight() + 2 * Parser::getWidth()) < 50) {
        _score += 100;
        _nbEnnemies++;
        resetGame();
    }
    return (true);
}

void LibQix::addFloor(int x, int y)
{
    unsigned long long int indexID = _instance.newEntity()._id;

    _typeStorage.addComponentForEntity(indexID);
    _typeStorage.getComponentForEntity(indexID) = Tag{indexID, FLOOR};
    _positionStorage.addComponentForEntity(indexID);
    _walkableStorage.addComponentForEntity(indexID);
    _positionStorage.getComponentForEntity(indexID) = Position{indexID, x, y};
    _walkableStorage.getComponentForEntity(indexID) = Walkable{indexID, 1, 1};
}

void LibQix::addWall(int x, int y)
{
    unsigned long long int indexID = _instance.newEntity()._id;

    _typeStorage.addComponentForEntity(indexID);
    _typeStorage.getComponentForEntity(indexID) = Tag{indexID, WALL_1};
    _positionStorage.addComponentForEntity(indexID);
    _positionStorage.getComponentForEntity(indexID) = Position{indexID, x, y};
    _colliderStorage.addComponentForEntity(indexID);
    _colliderStorage.getComponentForEntity(indexID) = Collider{indexID, 1, 1};
    _velocityStorage.addComponentForEntity(indexID);
    _velocityStorage.getComponentForEntity(indexID) = Velocity{indexID, 0, 0};
}

int LibQix::getScore() const
{
    return (_score);
}

void LibQix::initBordervector(int xStart, int yStart)
{
    int length = Parser::getWidth();
    int height = Parser::getHeight() - 1;
    int xStartCpy = xStart;
    int yStartCpy = yStart;

    for (int i = xStart; i < xStart + length; i++) {
        _borderVector.emplace_back(i, yStartCpy);
        xStartCpy = i;
    }
    yStart++;
    for (int i = yStart; i < yStart + height; i++) {
        _borderVector.emplace_back(xStartCpy, i);
        yStartCpy = i;
    }
    xStartCpy--;
    for (int i = xStartCpy; i > xStartCpy - (length - 1); i--) {
        _borderVector.emplace_back(i, yStartCpy);
        xStart = i;
    }
    yStartCpy--;
    for (int i = yStartCpy; i > yStartCpy - (height - 1); i--) {
        _borderVector.emplace_back(xStart, i);
        yStart = i;
    }
}

void LibQix::getSurface()
{
    std::vector<std::pair<int, int>>::iterator first;
    std::vector<std::pair<int, int>>::iterator last;
    std::vector<std::pair<int, int>> surface_one;
    std::vector<std::pair<int, int>> surface_two;
    std::vector<std::pair<int, int>> copy;


    for (auto &it: _pathStorage.componentVector) {
        if (it.canMakePath || it.path.size() <= 1)
            continue;

        first = getBorderIteratorMatching(it.path.begin()->first, it.path.begin()->second);
        last = getBorderIteratorMatching(it.path.rbegin()->first, it.path.rbegin()->second);

        //start filling surface one
        while (std::distance(first, last) != 0) {
            if (first == _borderVector.end()) {;
                first = _borderVector.begin();
            } else {
                surface_one.emplace_back(first->first, first->second);
                first++;
            }
        }
        copy.assign(it.path.begin() + 1, it.path.end());
        std::reverse(copy.begin(), copy.end());
        surface_one.insert(surface_one.end(), copy.begin(), copy.end());
        //finished filling border of surface one
        copy.clear();
        first = getBorderIteratorMatching(it.path.begin()->first, it.path.begin()->second);

        //start filling surface two
        while (std::distance(first, last) != 0) {
            if (last == _borderVector.end()) {
                last = _borderVector.begin();
            } else {
                surface_two.emplace_back(last->first, last->second);
                last++;
            }
        }
        copy.assign(it.path.begin(), it.path.end() - 1);
        surface_two.insert(surface_two.end(), copy.begin(), copy.end());

        _borderVector.clear();
        if (surface_one.size() > surface_two.size()) {
            fillSurface(surface_two);
            _borderVector.assign(surface_one.begin(), surface_one.end());
            _score += surface_two.size();
        } else {
            fillSurface(surface_one);
            _borderVector.assign(surface_two.begin(), surface_two.end());
            _score += surface_one.size();
        }
        it.path.clear();
    }
}

std::vector<std::pair<int, int>>::iterator LibQix::getBorderIteratorMatching(int x, int y)
{
    std::vector<std::pair<int, int>>::iterator it;

    for (it = _borderVector.begin();  it != _borderVector.end(); it++) {
        if (x == it->first && y == it->second) {
            return (it);
        }
    }
    return (it);
}

void LibQix::fillSurface(const std::vector<std::pair<int, int>> &surfaceBorder)
{
    TypeEntity type;
    int top = getTopPosition(surfaceBorder);
    int bottom = getBottomPosition(surfaceBorder);

    for (auto &bloc: _positionStorage.componentVector) {
        type = _typeStorage.getComponentForEntity(bloc.entityId).type;
        if (type == PLAYER_1 || type == ENEMY_1 || type == WALL_1 || type == WALL_2 || type == WALL_3)
            continue;
        else if (bloc.y < top || bloc.y > bottom)
            continue;

        if (isInSurfaceAtLine(bloc.x, bloc.y, surfaceBorder))
            _typeStorage.getComponentForEntity(bloc.entityId).type = WALL_3;
    }
}

int LibQix::getLeftPositionAtLine(int y,
    const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    int left = Parser::getLeft() + Parser::getWidth();

    for (auto &pos: surfaceBorder) {
        if (pos.second != y)
            continue;
        if (pos.first < left)
            left = pos.first;
    }
    return (left);
}

int LibQix::getRightPositionAtLine(int y,
    const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    int right = Parser::getLeft();

    for (auto &pos: surfaceBorder) {
        if (pos.second != y)
            continue;
        if (pos.first > right)
            right = pos.first;
    }
    return (right);
}

int LibQix::getTopPosition(const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    int top = Parser::getHeight() + Parser::getTop();

    for (auto &pos: surfaceBorder) {
        if (pos.second < top)
            top = pos.second;
    }
    return (top);
}

int LibQix::getBottomPosition(const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    int bottom = Parser::getTop();

    for (auto &pos: surfaceBorder) {
        if (pos.second > bottom)
            bottom = pos.second;
    }
    return (bottom);
}

bool LibQix::isInSurfaceAtLine(int x, int y, const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    bool inSurface = true;
    int left = getLeftPositionAtLine(y, surfaceBorder);
    int secondLeft = getRightPositionAtLine(y, surfaceBorder);
    int right = secondLeft;
    int top = getTopPositionAtLine(x, surfaceBorder);
    int bottom = getBottomPositionAtLine(x, surfaceBorder);
    std::vector<std::pair<int, int>>::const_iterator it = surfaceBorder.begin();

    if (x <= left || x >= right)
        return (false);
    else if (y <= top || y >= bottom)
        return (false);
    while (left != right) {
        if (it == surfaceBorder.end()) {
            if (secondLeft > x)
                break;
            if (left + 1 != secondLeft)
                inSurface = !inSurface;
            left = secondLeft;
            secondLeft = right;
            it = surfaceBorder.begin();
        } else {
            if (it->second == y && it->first > left && it->first < secondLeft) {
                secondLeft = it->first;
            }
            it++;
        }
    }
    return (inSurface);
}

int LibQix::getTopPositionAtLine(int x,
    const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    int top = Parser::getTop();
    int secondTop = Parser::getTop() + Parser::getHeight();
    std::vector<std::pair<int, int>>::const_iterator it = surfaceBorder.begin();

    while (top < Parser::getTop()  + Parser::getHeight()) {
        if (it == surfaceBorder.end()) {
            if (top + 1 < secondTop)
                break;
            top = secondTop;
            secondTop = Parser::getTop() + Parser::getHeight();
            it = surfaceBorder.begin();
        } else {
            if (it->first == x && it->second > top && it->second < secondTop) {
                secondTop = it->second;
            }
            it++;
        }
    }
    return (top);
}

int LibQix::getBottomPositionAtLine(int x,
    const std::vector<std::pair<int, int>> &surfaceBorder
) const
{
    int bottom = Parser::getTop() + Parser::getHeight();
    int secondBottom = Parser::getTop();
    std::vector<std::pair<int, int>>::const_iterator it = surfaceBorder.begin();

    while (bottom > Parser::getTop()) {
        if (it == surfaceBorder.end()) {
            if (bottom - 1 > secondBottom)
                break;
            bottom = secondBottom;
            secondBottom = Parser::getTop();
            it = surfaceBorder.begin();
        } else {
            if (it->first == x && it->second < bottom && it->second > secondBottom) {
                secondBottom = it->second;
            }
            it++;
        }
    }
    return (bottom);
}

std::pair<int, int> LibQix::getRandomBorderPos() const
{
    int value = rand() % _borderVector.size();

    for (auto& it: _borderVector) {
        value--;
        if (value == 0)
            return (it);
    }
    return (std::make_pair(Parser::getTop(), Parser::getLeft()));
}

extern "C" IGameModule *entryPoint()
{
    return (new LibQix());
}


