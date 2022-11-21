/*
** EPITECH PROJECT, 2020
** local arcade
** File description:
** LibSolar
*/

#include "../include/LibSolar.hpp"

LibSolar::LibSolar() {
    srand(time(nullptr));
    unsigned long long int floorID = 0;

    for (int y = 0; y < 29; y++) {
        if (y < 2 || y > 26)
            continue;
        for (int x = 0; x < 29; x++) {
            if (((x + 1) % 3 != 0 && (y + 1) % 3 != 0) || (x < 2 || x > 26))
                continue;
            floorID = _instance.newEntity()._id;
            _typeStorage.addComponentForEntity(floorID);
            _typeStorage.getComponentForEntity(floorID) = Tag{floorID, FLOOR};
            _positionStorage.addComponentForEntity(floorID);
            _walkableStorage.addComponentForEntity(floorID);
            _positionStorage.getComponentForEntity(floorID) = Position{floorID, x, y};
            _walkableStorage.getComponentForEntity(floorID) = Walkable{floorID, 1, 1};
        }
    }
    ECSEntity player = _instance.newEntity();
    _positionStorage.addComponentForEntity(player._id);
    _positionStorage.getComponentForEntity(player._id) = Position{player._id, 14, 14};
    _velocityStorage.addComponentForEntity(player._id);
    _velocityStorage.getComponentForEntity(player._id) = Velocity{player._id, 0, 0};
    _colliderStorage.addComponentForEntity(player._id);
    _colliderStorage.getComponentForEntity(player._id) = Collider{player._id, 1, 1};
    _typeStorage.addComponentForEntity(player._id);
    _typeStorage.getComponentForEntity(player._id) = Tag{player._id, PLAYER_1};
    _clockStorage.addComponentForEntity(player._id);
    _clockStorage.getComponentForEntity(player._id) = Clock{player._id, 0, 8};
    _playableStorage.addComponentForEntity(player._id);

    std::vector<std::vector<int>> enemyPos{{20, 1, 1, 0}, {1, 3, 0, -1}, {10, 27, 1, 0}, {27, 25, 0, -1}};
    for (int i = 0; i < 4; i++) {
        ECSEntity enemy = _instance.newEntity();
        _positionStorage.addComponentForEntity(enemy._id);
        _positionStorage.getComponentForEntity(enemy._id) = Position{enemy._id, enemyPos[i][0], enemyPos[i][1]};
        _typeStorage.addComponentForEntity(enemy._id);
        _typeStorage.getComponentForEntity(enemy._id) = Tag{enemy._id, ENEMY_1};
        _clockStorage.addComponentForEntity(enemy._id);
        _clockStorage.getComponentForEntity(enemy._id) = Clock{enemy._id, 0, 8};
        _velocityStorage.addComponentForEntity(enemy._id);
        _velocityStorage.getComponentForEntity(enemy._id) = Velocity{enemy._id, enemyPos[i][2], enemyPos[i][3]};
    }

    for (int i = 0; i < 10; ++i) {
        int x = (((std::rand() % 9) + 1) * 3 - 1);
        int y = (((std::rand() % 9) + 1) * 3 - 1);
        for (auto & it: _positionStorage.componentVector) {
            if (it.x == x && it.y == y) {
                _typeStorage.getComponentForEntity(it.entityId).type = BONUS_1;
                _collectibleStorage.addComponentForEntity(it.entityId);
            }
        }
    }
}

LibSolar::~LibSolar() {}

void LibSolar::receiveEvent(KeyBind key) {
    //unsigned long long int clock = static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _clock).count());
    unsigned long long int playerID = _playableStorage.componentVector[0].entityId;
    int requestedX = _positionStorage.getComponentForEntity(playerID).x;
    int requestedY = _positionStorage.getComponentForEntity(playerID).y;

    switch (key) {
    case KeyBind::ARROWUP:
        requestedY--;
        if (_velocityStorage.getComponentForEntity(playerID).yOffset == 1)
            return;
        if (_velocityStorage.getComponentForEntity(playerID).yOffset == -1)
            _clockStorage.getComponentForEntity(playerID) = Clock{playerID, _clockStorage.getComponentForEntity(playerID).tickCount, 4};
        break;
    case KeyBind::ARROWRIGHT:
        requestedX++;
        if (_velocityStorage.getComponentForEntity(playerID).xOffset == -1)
            return;
        if (_velocityStorage.getComponentForEntity(playerID).xOffset == 1)
            _clockStorage.getComponentForEntity(playerID) = Clock{playerID, _clockStorage.getComponentForEntity(playerID).tickCount, 4};
        break;
    case KeyBind::ARROWDOWN:
        requestedY++;
        if (_velocityStorage.getComponentForEntity(playerID).yOffset == -1)
            return;
        if (_velocityStorage.getComponentForEntity(playerID).yOffset == 1)
            _clockStorage.getComponentForEntity(playerID) = Clock{playerID, _clockStorage.getComponentForEntity(playerID).tickCount, 4};
        break;
    case KeyBind::ARROWLEFT:
        requestedX--;
        if (_velocityStorage.getComponentForEntity(playerID).xOffset == 1)
            return;
        if (_velocityStorage.getComponentForEntity(playerID).xOffset == -1)
            _clockStorage.getComponentForEntity(playerID) = Clock{playerID, _clockStorage.getComponentForEntity(playerID).tickCount, 4};
        break;
    default:
        _clockStorage.getComponentForEntity(playerID) = Clock{playerID, _clockStorage.getComponentForEntity(playerID).tickCount, 8};
        break;
    }
    if (requestedX < 2 || requestedX > 27 || requestedY < 2 || requestedY > 27)
        return;
    if ((requestedX + 1) % 3 != 0 && (requestedY + 1) % 3 != 0) {
        return;
    }
    if (key == KeyBind::F)
        playerShoot(playerID);
    _inputSystem.update(&_playableStorage, &_velocityStorage, key);
}

void LibSolar::playerShoot(unsigned long long playerID) {
    ECSEntity bullet = _instance.newEntity();
    
    if (_velocityStorage.getComponentForEntity(playerID).xOffset == 0 && _velocityStorage.getComponentForEntity(playerID).yOffset == 0)
        return;
    for (auto &it:_shootingStorage.componentVector) {
        if (it.target == BULLET)
            return;
    }
    _positionStorage.addComponentForEntity(bullet._id);
    _velocityStorage.addComponentForEntity(bullet._id);
    _velocityStorage.getComponentForEntity(bullet._id) = Velocity{bullet._id, _velocityStorage.getComponentForEntity(playerID).xOffset, _velocityStorage.getComponentForEntity(playerID).yOffset};
    _positionStorage.getComponentForEntity(bullet._id) = Position{bullet._id, _positionStorage.getComponentForEntity(playerID).x + (_velocityStorage.getComponentForEntity(playerID).xOffset * 2), _positionStorage.getComponentForEntity(playerID).y + (_velocityStorage.getComponentForEntity(playerID).yOffset * 2)};
    _typeStorage.addComponentForEntity(bullet._id);
    _typeStorage.getComponentForEntity(bullet._id) = Tag{bullet._id, BULLET};
    _clockStorage.addComponentForEntity(bullet._id);
    _clockStorage.getComponentForEntity(bullet._id) = Clock{bullet._id, 0, 2};
    _shootingStorage.addComponentForEntity(bullet._id);
    _shootingStorage.getComponentForEntity(bullet._id) = Shooting{bullet._id, PLAYER_1, 0, 8};
    _colliderStorage.addComponentForEntity(bullet._id);
    _colliderStorage.getComponentForEntity(bullet._id) = Collider{bullet._id, 1, 1};
}


const std::vector<Entity *> &LibSolar::getEntities() {
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

bool LibSolar::isPlayerAlive() {
    for (auto &it: _typeStorage.componentVector) {
        if (it.type == PLAYER_1)
            return true;
    }
    return false;
}

bool LibSolar::playerWin() {
    for (auto &it: _typeStorage.componentVector) {
        if (it.type == BONUS_1)
            return false;
    }
    return true;
}

bool LibSolar::oneCycleLoop() {
    //unsigned long long int clock = static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _clock).count());
    //int prob = 1;
    _clockSystem.update(&_clockStorage);
    for (const auto &it: _instance._entityList) {
        if (_typeStorage.getComponentForEntity(it._id).type != ENEMY_1)
            continue;
        if (_positionStorage.getComponentForEntity(it._id).y == 1) {
            if (_positionStorage.getComponentForEntity(it._id).x <= 3)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, 1, 0};
            if (_positionStorage.getComponentForEntity(it._id).x >= 25)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, -1, 0};
        }
        if (_positionStorage.getComponentForEntity(it._id).y == 27) {
            if (_positionStorage.getComponentForEntity(it._id).x <= 3)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, 1, 0};
            if (_positionStorage.getComponentForEntity(it._id).x >= 25)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, -1, 0};
        }

        if (_positionStorage.getComponentForEntity(it._id).x == 1) {
            if (_positionStorage.getComponentForEntity(it._id).y <= 3)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, 0, 1};
            if (_positionStorage.getComponentForEntity(it._id).y >= 25)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, 0, -1};
        }
        if (_positionStorage.getComponentForEntity(it._id).x == 27) {
            if (_positionStorage.getComponentForEntity(it._id).y <= 3)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, 0, 1};
            if (_positionStorage.getComponentForEntity(it._id).y >= 25)
                _velocityStorage.getComponentForEntity(it._id) = Velocity{it._id, 0, -1};
        }
        if (_clockStorage.getComponentForEntity(it._id).tickCount >= _clockStorage.getComponentForEntity(it._id).limit)
            ennemyShoot(it._id);
    }
    _collisionSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_shootingStorage, &_typeStorage, &_clockStorage);
    if (!isPlayerAlive() || playerWin())
        return false;
    _floorSystem.update(&_positionStorage, &_velocityStorage, &_colliderStorage, &_walkableStorage, &_shootingStorage);
    _movementSystem.update(&_positionStorage, &_velocityStorage, &_clockStorage);
    _shootingSystem.update(&_shootingStorage, &_clockStorage, &_typeStorage, &_positionStorage, &_velocityStorage);
    if (_collectibleSystem.update(&_collectibleStorage, &_typeStorage, &_positionStorage, &_playableStorage)) {
        _score += 100;
    }
    return true;
}

int LibSolar::getScore() const {
    return 0;
}

void LibSolar::ennemyShoot(unsigned long long id) {
    int prob = 10;

    if ((rand() % 100) > prob)
        return;
    ECSEntity bullet = _instance.newEntity();
    _positionStorage.addComponentForEntity(bullet._id);
    _velocityStorage.addComponentForEntity(bullet._id);
    _positionStorage.getComponentForEntity(bullet._id) = Position{bullet._id, _positionStorage.getComponentForEntity(id).x, _positionStorage.getComponentForEntity(id).y};
    _typeStorage.addComponentForEntity(bullet._id);
    _typeStorage.getComponentForEntity(bullet._id) = Tag{bullet._id, BULLET};
    _clockStorage.addComponentForEntity(bullet._id);
    _clockStorage.getComponentForEntity(bullet._id) = Clock{bullet._id, 0, 2};
    _shootingStorage.addComponentForEntity(bullet._id);
    _shootingStorage.getComponentForEntity(bullet._id) = Shooting{bullet._id, PLAYER_1, 0, 50};
    _colliderStorage.addComponentForEntity(bullet._id);
    _colliderStorage.getComponentForEntity(bullet._id) = Collider{bullet._id, 1, 1};
    if (_positionStorage.getComponentForEntity(id).y == 1) {
        _velocityStorage.getComponentForEntity(bullet._id) = Velocity{bullet._id, 0, 1};
    }
    if (_positionStorage.getComponentForEntity(id).y == 27) {
        _velocityStorage.getComponentForEntity(bullet._id) = Velocity{bullet._id, 0, -1};
    }
    if (_positionStorage.getComponentForEntity(id).x == 1) {
        _velocityStorage.getComponentForEntity(bullet._id) = Velocity{bullet._id, 1, 0};
    }
    if (_positionStorage.getComponentForEntity(id).x == 27) {
        _velocityStorage.getComponentForEntity(bullet._id) = Velocity{bullet._id, -1, 0};
    }
}

extern "C" IGameModule *entryPoint() {
    return (new LibSolar());
}