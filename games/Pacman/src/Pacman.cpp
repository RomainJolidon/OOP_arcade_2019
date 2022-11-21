/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include <zconf.h>
#include "../include/Pacman.hpp"

void Pacman::createWallAtPosition(int x, int y)
{
    unsigned long long int wallID = _instance.newEntity()._id;
    _typeStorage.addComponentForEntity(wallID);
    _typeStorage.getComponentForEntity(wallID) = Tag{wallID, WALL_1};
    _positionStorage.addComponentForEntity(wallID);
    _velocityStorage.addComponentForEntity(wallID);
    _colliderStorage.addComponentForEntity(wallID);
    _positionStorage.getComponentForEntity(wallID) = Position{
        wallID, x, y, x, y};
    _velocityStorage.getComponentForEntity(wallID) = Velocity{
        wallID, 0, 0};
    _colliderStorage.getComponentForEntity(wallID) = Collider{
        wallID, 1, 1};
}

void Pacman::createFloorAtPosition(int x, int y)
{
    unsigned long long int floorID = _instance.newEntity()._id;
    _typeStorage.addComponentForEntity(floorID);
    _positionStorage.addComponentForEntity(floorID);
    _typeStorage.getComponentForEntity(floorID) = Tag{floorID,
        FLOOR};
    _positionStorage.getComponentForEntity(floorID) = Position{
        floorID, x, y, x, y};
}

void Pacman::createBonusAtPosition(int x, int y, Effect effect, TypeEntity bonusType)
{
    unsigned long long int bonusID = _instance.newEntity()._id;
    _typeStorage.addComponentForEntity(bonusID);
    _colliderStorage.addComponentForEntity(bonusID);
    _positionStorage.addComponentForEntity(bonusID);
    _bonusStorage.addComponentForEntity(bonusID);
    _bonusStorage.getComponentForEntity(bonusID) = Bonus{bonusID, effect};
    _typeStorage.getComponentForEntity(bonusID) = Tag{bonusID,
        bonusType};
    _colliderStorage.getComponentForEntity(bonusID) = Collider{
        bonusID, 1, 1};
    _positionStorage.getComponentForEntity(bonusID) = Position{
        bonusID, x, y, x, y};
}

void Pacman::createAllEntities()
{
    static int baseClock = 3;
    if (baseClock > 1)
        baseClock--;
    _gameSpeed = baseClock;
    for (int y = 0; y < 21; y++) {  //31
        for (int x = 0; x < 21; x++) {  //60
            if (y == 0)
                createWallAtPosition(x, y);
            else if (y == 1 && (x == 0 || x == 1 || x == 10 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 2 && (x != 2 && x != 5 && x != 9 && x != 11 && x != 15 && x != 18))
                createWallAtPosition(x, y);
            else if (y == 2 && (x == 2 || x == 18))
                createBonusAtPosition(x, y, SUPERBONUS1, BONUS_2);
            else if (y == 3 && (x == 0 || x == 1 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 4 && (x != 2 && x != 5 && x != 7 && x != 13 && x != 15 && x != 18))
                createWallAtPosition(x, y);
            else if (y == 5 && (x == 0 || x == 1 || x == 6 || x == 10 || x == 14 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 6 && (x != 5 && x != 9 && x != 11 && x != 15))
                createWallAtPosition(x, y);
            else if (y == 7 && ((x >= 0 && x <= 4) || x == 6 || x == 14 || (x >= 16 && x <= 20)))
                createWallAtPosition(x, y);
            else if (y == 7 && (x > 6 && x < 14))
                createFloorAtPosition(x, y);
            else if (y == 8 && (x != 5 && x != 7 && x != 10 && x != 13 && x != 15))
                createWallAtPosition(x, y);
            else if (y == 8 && (x == 0 || x == 7 || x == 10 || x == 13 || x == 20))
                createFloorAtPosition(x, y);
            else if (y == 9 && (x == 8 || x == 12))
                createWallAtPosition(x, y);
            else if (y == 9 && (x != 5 && x != 8 && x != 12 && x != 15))
                createFloorAtPosition(x, y);
            else if (y == 10 && (x != 5 && x != 7 && x != 13 && x != 15))
                createWallAtPosition(x, y);
            else if (y == 10 && (x == 7 || x == 13))
                createFloorAtPosition(x, y);
            else if (y == 11 && ((x >= 0 && x <= 4) || x == 6 || x == 14 || (x >= 16 && x <= 20)))
                createWallAtPosition(x, y);
            else if (y == 11 && (x > 6 && x < 14))
                createFloorAtPosition(x, y);
            else if (y == 12 && (x != 5 && x != 7 && x != 13 && x != 15))
                createWallAtPosition(x, y);
            else if (y == 12 && (x == 7 || x == 13))
                createFloorAtPosition(x, y);
            else if (y == 13 && (x == 0 || x == 1 || x == 10 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 14 && (x != 2 && x != 5 && x != 9 && x != 11 && x != 15 && x != 18))
                createWallAtPosition(x, y);
            else if (y == 15 && (x == 0 || x == 1 || x == 4 || x == 16 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 15 && (x == 2 || x == 18))
                createBonusAtPosition(x, y, SUPERBONUS1, BONUS_2);
            else if (y == 16 && (x != 3 && x != 5 && x != 7 && x != 13 && x != 15 && x != 17))
                createWallAtPosition(x, y);
            else if (y == 17 && (x == 0 || x == 1 || x == 6 || x == 10 || x == 14 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 18 && (x != 2 && x != 9 && x != 11 && x != 18))
                createWallAtPosition(x, y);
            else if (y == 19 && (x == 0 || x == 1 || x == 19 || x == 20))
                createWallAtPosition(x, y);
            else if (y == 20)
                createWallAtPosition(x, y);
            else
                createBonusAtPosition(x, y, BONUS1, BONUS_1);
        }
    }
    ECSEntity player = _instance.newEntity();
    ECSEntity enemy = _instance.newEntity();
    ECSEntity enemy1 = _instance.newEntity();
    ECSEntity enemy2 = _instance.newEntity();

    _positionStorage.addComponentForEntity(player._id);
    _positionStorage.addComponentForEntity(enemy._id);
    _positionStorage.addComponentForEntity(enemy1._id);
    _positionStorage.addComponentForEntity(enemy2._id);
    _positionStorage.getComponentForEntity(player._id) = Position{player._id, 10, 15, 10, 15};
    _positionStorage.getComponentForEntity(enemy._id) = Position{enemy._id, 9, 9, 9, 9};
    _positionStorage.getComponentForEntity(enemy1._id) = Position{enemy1._id, 10, 9, 10, 9};
    _positionStorage.getComponentForEntity(enemy2._id) = Position{enemy2._id, 11, 9, 11, 9};

    _velocityStorage.addComponentForEntity(player._id);
    _velocityStorage.addComponentForEntity(enemy._id);
    _velocityStorage.addComponentForEntity(enemy1._id);
    _velocityStorage.addComponentForEntity(enemy2._id);
    _velocityStorage.getComponentForEntity(player._id) = Velocity{player._id, 0, 0};
    _velocityStorage.getComponentForEntity(enemy._id) = Velocity{enemy._id, 1, 0};
    _velocityStorage.getComponentForEntity(enemy1._id) = Velocity{enemy1._id, 1, 0};
    _velocityStorage.getComponentForEntity(enemy2._id) = Velocity{enemy2._id, 1, 0};

    _colliderStorage.addComponentForEntity(player._id);
    _colliderStorage.addComponentForEntity(enemy._id);
    _colliderStorage.addComponentForEntity(enemy1._id);
    _colliderStorage.addComponentForEntity(enemy2._id);
    _colliderStorage.getComponentForEntity(player._id) = Collider{player._id, 1, 1};
    _colliderStorage.getComponentForEntity(enemy._id) = Collider{enemy._id, 1, 1};
    _colliderStorage.getComponentForEntity(enemy1._id) = Collider{enemy1._id, 1, 1};
    _colliderStorage.getComponentForEntity(enemy2._id) = Collider{enemy2._id, 1, 1};

    _typeStorage.addComponentForEntity(player._id);
    _typeStorage.addComponentForEntity(enemy._id);
    _typeStorage.addComponentForEntity(enemy1._id);
    _typeStorage.addComponentForEntity(enemy2._id);
    _typeStorage.getComponentForEntity(player._id) = Tag{player._id, PLAYER_1};
    _typeStorage.getComponentForEntity(enemy._id) = Tag{enemy._id, ENEMY_1};
    _typeStorage.getComponentForEntity(enemy1._id) = Tag{enemy1._id, ENEMY_1};
    _typeStorage.getComponentForEntity(enemy2._id) = Tag{enemy2._id, ENEMY_1};

    _clockStorage.addComponentForEntity(player._id);
    _clockStorage.addComponentForEntity(enemy._id);
    _clockStorage.addComponentForEntity(enemy1._id);
    _clockStorage.addComponentForEntity(enemy2._id);
    _clockStorage.getComponentForEntity(player._id) = Clock{player._id, 0, _gameSpeed};
    _clockStorage.getComponentForEntity(enemy._id) = Clock{enemy._id, 0, 999999};
    _clockStorage.getComponentForEntity(enemy1._id) = Clock{enemy1._id, 0, 999999};
    _clockStorage.getComponentForEntity(enemy2._id) = Clock{enemy2._id, 0, 999999};

    _playableStorage.addComponentForEntity(player._id);
    _playableStorage.getComponentForEntity(player._id) = Playable{player._id, NONE, NOEFFECT};

    _AIStorage.addComponentForEntity(enemy._id);
    _AIStorage.addComponentForEntity(enemy1._id);
    _AIStorage.addComponentForEntity(enemy2._id);
}

void Pacman::emptyAllEntities()
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
    _bonusStorage.componentVector.clear();
    _bonusStorage.entityIdxToComponentIdxMap.clear();

}

void Pacman::resetGame()
{
    emptyAllEntities();
    createAllEntities();
}

Pacman::Pacman()
{
    _score = 0;
    srand(time(NULL));
    createAllEntities();
}

Pacman::~Pacman()
{
}

void Pacman::receiveEvent(KeyBind key)
{
    _input = key;
}

const std::vector<Entity *> &Pacman::getEntities()
{
    int x;
    int y;
    TypeEntity type;
    _entities.clear();
    for (const auto& it : _instance._entityList) {
        if (_typeStorage.hasEntityComponent(it._id)) {
            x = _positionStorage.getComponentForEntity(it._id).x;
            y = _positionStorage.getComponentForEntity(it._id).y;
            type = _typeStorage.getComponentForEntity(it._id).type;
            _entities.push_back(new Entity(type, x, y));
        }
    }
    return _entities;
}

bool Pacman::oneCycleLoop()
{
    static int count = 0;
    count++;
    if (count > 100) {
        for (auto it : _AIStorage.entityIdxToComponentIdxMap)
            _clockStorage.getComponentForEntity(it.first).limit = _gameSpeed;
    }
    _clockSystem.update(&_clockStorage);
    _collisionSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_typeStorage, &_playableStorage, &_bonusStorage);
    if (_playableStorage.componentVector.empty())
        return false;
    else if(_bonusStorage.componentVector.empty()) {
        resetGame();
        count = 0;
    }
    _score = _bonusEffectSystem.update(&_playableStorage, &_AIStorage, &_bonusStorage, &_typeStorage, _score);
    _movementSystem.update(&_positionStorage, &_velocityStorage, &_clockStorage);
    _inputSystem.update(&_playableStorage, &_velocityStorage, _input);
    _AISystem.update(&_AIStorage, &_velocityStorage);
    return true;
}

int Pacman::getScore() const
{
    return _score;
}

extern "C" IGameModule *entryPoint()
{
    return (new Pacman());
}