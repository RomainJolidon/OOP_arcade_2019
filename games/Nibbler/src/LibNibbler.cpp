/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/LibNibbler.hpp"

LibNibbler::LibNibbler()
: _score(0)
{
    srand(time(NULL));

    //Map creation
    std::list<std::string> map = Parser::parseMap("games/Nibbler/map/map_01", 6, 20);
    int x = 0;
    int y = Parser::getTop();

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
                addBonus(x, y);
                break;
            default:
                break;
            }
            x++;
        }
        y++;
    }

    addRandomBonus();
    //Player creation
    ECSEntity player = _instance.newEntity();

    _positionStorage.addComponentForEntity(player._id);
    _positionStorage.getComponentForEntity(player._id) = Position{player._id, 28, 18};
    _velocityStorage.addComponentForEntity(player._id);
    _velocityStorage.getComponentForEntity(player._id) = Velocity{player._id, 1, 0};
    _colliderStorage.addComponentForEntity(player._id);
    _colliderStorage.getComponentForEntity(player._id) = Collider{player._id, 1, 1};
    _typeStorage.addComponentForEntity(player._id);
    _typeStorage.getComponentForEntity(player._id) = Tag{player._id, PLAYER_1};
    _clockStorage.addComponentForEntity(player._id);
    _clockStorage.getComponentForEntity(player._id) = Clock{player._id, 0, 4};

    _playableStorage.addComponentForEntity(player._id);
    _playableStorage.getComponentForEntity(player._id) = Playable{player._id, ARROWRIGHT};

    _targetId = player._id;
    for (int i = 0; i < 5; i++) {
        addFollower(_targetId);
    }
}

LibNibbler::~LibNibbler()
{
}

void LibNibbler::receiveEvent(KeyBind key)
{
    _inputSystem.update(&_playableStorage, &_velocityStorage, key);
}

const std::vector<Entity *> &LibNibbler::getEntities()
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

bool LibNibbler::oneCycleLoop()
{
    _clockSystem.update(&_clockStorage);
    _floorSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_walkableStorage);
    _collisionSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_followerStorage);
    if (!_movementSystem.update(&_positionStorage, &_velocityStorage, &_clockStorage, &_followerSystem, &_followerStorage))
        return (false);
    if (_collectibleSystem.update(&_collectibleStorage, &_typeStorage, &_positionStorage, &_playableStorage)) {
        _score += 100;
        addRandomBonus();
        addFollower(_targetId);
    }
    return (true);
}

void LibNibbler::addFloor(int x, int y)
{
    unsigned long long int indexID = _instance.newEntity()._id;

    _typeStorage.addComponentForEntity(indexID);
    _typeStorage.getComponentForEntity(indexID) = Tag{indexID, FLOOR};
    _positionStorage.addComponentForEntity(indexID);
    _walkableStorage.addComponentForEntity(indexID);
    _positionStorage.getComponentForEntity(indexID) = Position{indexID, x, y};
    _walkableStorage.getComponentForEntity(indexID) = Walkable{indexID, 1, 1};
}

void LibNibbler::addWall(int x, int y)
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

void LibNibbler::addBonus(int x, int y)
{

    for (auto & it: _positionStorage.componentVector) {
        if (it.x == x && it.y == y) {
            _typeStorage.getComponentForEntity(it.entityId).type = BONUS_1;
            _collectibleStorage.addComponentForEntity(it.entityId);
            return;
        }
    }
}

void LibNibbler::addRandomBonus()
{
    int xPos = (Parser::getLeft() + rand() % (Parser::getWidth() - 2)) + 1;
    int yPos = (Parser::getTop()+ rand() % (Parser::getHeight() - 2))  + 1;

    addBonus(xPos, yPos);
}

unsigned long long int LibNibbler::addFollower(unsigned long long int targetId)
{
    int x = 0;
    int y = 0;
    Follower follower;
    unsigned long long int indexID;

    if (_followerStorage.hasEntityComponent(targetId)) {
        if (_velocityStorage.getComponentForEntity(targetId).xOffset != 0 || _velocityStorage.getComponentForEntity(targetId).yOffset != 0) {
            x = _positionStorage.getComponentForEntity(targetId).x + -(_velocityStorage.getComponentForEntity(targetId).xOffset);
            y = _positionStorage.getComponentForEntity(targetId).y + -(_velocityStorage.getComponentForEntity(targetId).yOffset);
            follower.xSave = _velocityStorage.getComponentForEntity(targetId).xOffset;
            follower.ySave = _velocityStorage.getComponentForEntity(targetId).yOffset;
        } else {
            x = _positionStorage.getComponentForEntity(targetId).x + -_followerStorage.getComponentForEntity(targetId).xSave;
            y = _positionStorage.getComponentForEntity(targetId).y + _followerStorage.getComponentForEntity(targetId).ySave;
            follower.xSave = _followerStorage.getComponentForEntity(targetId).xSave;
            follower.ySave = _followerStorage.getComponentForEntity(targetId).ySave;
        }
    } else {
        if (_velocityStorage.getComponentForEntity(targetId).xOffset != 0 && _velocityStorage.getComponentForEntity(targetId).yOffset != 0) {
            x = _positionStorage.getComponentForEntity(targetId).x + -_velocityStorage.getComponentForEntity(targetId).xOffset;
            y = _positionStorage.getComponentForEntity(targetId).y + _velocityStorage.getComponentForEntity(targetId).yOffset;
            follower.xSave = _velocityStorage.getComponentForEntity(targetId).xOffset;
            follower.ySave = _velocityStorage.getComponentForEntity(targetId).yOffset;
        } else {
            x = _positionStorage.getComponentForEntity(targetId).x - 1;
            y = _positionStorage.getComponentForEntity(targetId).y;
            follower.xSave = 1;
            follower.ySave = 0;
        }
    }
    indexID = _instance.newEntity()._id;
    follower.entityId = indexID;
    follower.targetId = targetId;
    _positionStorage.addComponentForEntity(indexID);
    _positionStorage.getComponentForEntity(indexID) = Position{indexID, x, y};
    _velocityStorage.addComponentForEntity(indexID);
    _velocityStorage.getComponentForEntity(indexID) = Velocity{indexID, _positionStorage.getComponentForEntity(targetId).x - x, _positionStorage.getComponentForEntity(targetId).y - y};
    _colliderStorage.addComponentForEntity(indexID);
    _colliderStorage.getComponentForEntity(indexID) = Collider{indexID, 1, 1};
    _typeStorage.addComponentForEntity(indexID);
    _typeStorage.getComponentForEntity(indexID) = Tag{indexID, PLAYER_1};
    _followerStorage.addComponentForEntity(indexID);
    _followerStorage.getComponentForEntity(indexID) = follower;

    _targetId = indexID;
    return (indexID);
}

int LibNibbler::getScore() const
{
    return (_score);
}

extern "C" IGameModule *entryPoint()
{
    return (new LibNibbler());
}


