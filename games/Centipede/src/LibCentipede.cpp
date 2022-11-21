/*
** EPITECH PROJECT, 2020
** local arcade
** File description:
** LibCentipede
*/

#include "../include/LibCentipede.hpp"

LibCentipede::LibCentipede() {
    srand(time(nullptr));
    _centipedeRemain = 20;
    unsigned long long int floorID = 0, wallID = 0;

    for (int y = 1; y < 30; y++) {
        if (y == 23)
            continue;
        for (int x = 1; x < 30; x++) {
            floorID = _instance.newEntity()._id;
            _typeStorage.addComponentForEntity(floorID);
            _typeStorage.getComponentForEntity(floorID) = Tag{floorID, FLOOR};
            _positionStorage.addComponentForEntity(floorID);
            _walkableStorage.addComponentForEntity(floorID);
            _positionStorage.getComponentForEntity(floorID) = Position{floorID, x, y};
            _walkableStorage.getComponentForEntity(floorID) = Walkable{floorID, 1, 1};
        }
    }
    for (int i = 0; i <= 30; i++) {
        std::vector<std::vector<int>> pos = {{0, i}, {30, i}, {i, 0}, {i, 30}};

        for (int j = 0; j < 4; j++) {
            wallID = _instance.newEntity()._id;
            _typeStorage.addComponentForEntity(wallID);
            _typeStorage.getComponentForEntity(wallID) = Tag{wallID, WALL_1};
            _colliderStorage.addComponentForEntity(wallID);
            _colliderStorage.getComponentForEntity(wallID) = Collider{wallID, 1, 1};
            _positionStorage.addComponentForEntity(wallID);
            _positionStorage.getComponentForEntity(wallID) = Position{wallID, pos[j][0], pos[j][1]};
        }
    }
    for (int i = 0; i < 40; i++) {
        wallID = _instance.newEntity()._id;
        _typeStorage.addComponentForEntity(wallID);
        _typeStorage.getComponentForEntity(wallID) = Tag{wallID, WALL_1};
        _colliderStorage.addComponentForEntity(wallID);
        _colliderStorage.getComponentForEntity(wallID) = Collider{wallID, 1, 1};
        _positionStorage.addComponentForEntity(wallID);
        _positionStorage.getComponentForEntity(wallID) = Position{wallID, rand() % 29, rand() % 20 + 2};
        _damageStorage.addComponentForEntity(wallID);
        _damageStorage.getComponentForEntity(wallID) = Damage{wallID, 5};
    }
    ECSEntity player = _instance.newEntity();
    _positionStorage.addComponentForEntity(player._id);
    _positionStorage.getComponentForEntity(player._id) = Position{player._id, 15, 25};
    _velocityStorage.addComponentForEntity(player._id);
    _velocityStorage.getComponentForEntity(player._id) = Velocity{player._id, 0, 0};
    _colliderStorage.addComponentForEntity(player._id);
    _colliderStorage.getComponentForEntity(player._id) = Collider{player._id, 1, 1};
    _typeStorage.addComponentForEntity(player._id);
    _typeStorage.getComponentForEntity(player._id) = Tag{player._id, PLAYER_1};
    _clockStorage.addComponentForEntity(player._id);
    _clockStorage.getComponentForEntity(player._id) = Clock{player._id, 0, 4};
    _playableStorage.addComponentForEntity(player._id);
    createEnnemy(15, 1, 1, 12);
}

unsigned long long int LibCentipede::addFollower(unsigned long long int targetId)
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
        if (_velocityStorage.getComponentForEntity(targetId).xOffset != 0 || _velocityStorage.getComponentForEntity(targetId).yOffset != 0) {
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
    _typeStorage.getComponentForEntity(indexID) = Tag{indexID, ENEMY_1};
    _followerStorage.addComponentForEntity(indexID);
    _followerStorage.getComponentForEntity(indexID) = follower;

    return (indexID);
}

LibCentipede::~LibCentipede() {}

void LibCentipede::createEnnemy(int x, int y, int dir, int length) {
    unsigned long long int ennemyID = _instance.newEntity()._id;

    _positionStorage.addComponentForEntity(ennemyID);
    _positionStorage.getComponentForEntity(ennemyID) = Position{ennemyID, x, y};
    _velocityStorage.addComponentForEntity(ennemyID);
    _velocityStorage.getComponentForEntity(ennemyID) = Velocity{ennemyID, dir, 0};
    _colliderStorage.addComponentForEntity(ennemyID);
    _colliderStorage.getComponentForEntity(ennemyID) = Collider{ennemyID, 1, 1};
    _clockStorage.addComponentForEntity(ennemyID);
    _clockStorage.getComponentForEntity(ennemyID) = Clock{ennemyID, 0, 6};
    _typeStorage.addComponentForEntity(ennemyID);
    _typeStorage.getComponentForEntity(ennemyID) = Tag{ennemyID, ENEMY_1};
    for (int i = 0; i < length; i++) {
        ennemyID = addFollower(ennemyID);
    }
}

void LibCentipede::receiveEvent(KeyBind key) {
    unsigned long long int playerID = _playableStorage.componentVector[0].entityId;
    if (key == KeyBind::F && _shootingStorage.componentVector.size() == 0)
        playerShoot(playerID);
    _inputSystem.update(&_playableStorage, &_velocityStorage, key);
}

void LibCentipede::playerShoot(unsigned long long playerID) {
    ECSEntity bullet = _instance.newEntity();
    
    for (auto &it:_shootingStorage.componentVector) {
        if (it.target == BULLET)
            return;
    }
    _positionStorage.addComponentForEntity(bullet._id);
    _velocityStorage.addComponentForEntity(bullet._id);
    _velocityStorage.getComponentForEntity(bullet._id) = Velocity{bullet._id, 0, -1};
    _positionStorage.getComponentForEntity(bullet._id) = Position{bullet._id, _positionStorage.getComponentForEntity(playerID).x, _positionStorage.getComponentForEntity(playerID).y - 2};
    _typeStorage.addComponentForEntity(bullet._id);
    _typeStorage.getComponentForEntity(bullet._id) = Tag{bullet._id, BULLET};
    _clockStorage.addComponentForEntity(bullet._id);
    _clockStorage.getComponentForEntity(bullet._id) = Clock{bullet._id, 0, 1};
    _shootingStorage.addComponentForEntity(bullet._id);
    _shootingStorage.getComponentForEntity(bullet._id) = Shooting{bullet._id, ENEMY_1, 0, 100};
    _colliderStorage.addComponentForEntity(bullet._id);
    _colliderStorage.getComponentForEntity(bullet._id) = Collider{bullet._id, 1, 1};
}


const std::vector<Entity *> &LibCentipede::getEntities() {
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

bool LibCentipede::isPlayerAlive() {
    for (auto &it: _typeStorage.componentVector) {
        if (it.type == PLAYER_1)
            return true;
    }
    return false;
}

bool LibCentipede::playerWin() {
    for (auto &it: _typeStorage.componentVector) {
        if (it.type == BONUS_1)
            return false;
    }
    return true;
}

bool LibCentipede::oneCycleLoop() {
    _clockSystem.update(&_clockStorage);
    if (_collisionSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_shootingStorage, &_typeStorage, &_clockStorage, &_followerStorage, &_damageStorage, &_walkableStorage))
        _score += 100;
    _floorSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_walkableStorage, &_shootingStorage);
    _movementSystem.update(&_positionStorage, &_velocityStorage, &_clockStorage, &_typeStorage, &_followerSystem, &_followerStorage);
    _shootingSystem.update(&_shootingStorage, &_clockStorage, &_typeStorage, &_positionStorage, &_velocityStorage);
    for (auto &it: _typeStorage.componentVector) {
        if (it.type == ENEMY_1 && _positionStorage.getComponentForEntity(it.entityId).y == 23)
            return (false);
    }
    int ennemyNum = 0;
    for (auto &it: _typeStorage.componentVector) {
        if (it.type == ENEMY_1)
            ennemyNum++;
    }
    if (ennemyNum == 0) {
        _centipedeRemain--;
        if (_centipedeRemain != 0)
            createEnnemy(15, 1, 1, 12);
        else
            return false;
    }
    return true;
}

int LibCentipede::getScore() const {
    return 0;
}

extern "C" IGameModule *entryPoint() {
    return (new LibCentipede());
}