/*
** EPITECH PROJECT, 2020
** local arcade
** File description:
** LibSolar
*/

#ifndef LIBSOLAR_HPP_
#define LIBSOLAR_HPP_

#include <chrono>
#include "IGameModule.hpp"
#include "../ECS/include/Components.hpp"
#include "../ECS/include/Instance.hpp"
#include "../ECS/include/MovementSystem.hpp"
#include "../ECS/include/Storage.hpp"
#include "../ECS/include/InputSystem.hpp"
#include "../ECS/include/CollisionSystem.hpp"
#include "../ECS/include/FloorSystem.hpp"
#include "../ECS/include/AiSystem.hpp"
#include "../ECS/include/FollowerSystem.hpp"
#include "../ECS/include/CollectibleSystem.hpp"
#include "../ECS/include/ShootingSystem.hpp"
#include "../ECS/include/ClockSystem.hpp"

class LibSolar: public IGameModule {
    public:
        LibSolar();
        ~LibSolar();
        void receiveEvent(KeyBind key) override;
        const std::vector<Entity *> &getEntities() override;
        bool oneCycleLoop() override;
        int getScore() const override;
        void ennemyShoot(unsigned long long id);
        void playerShoot(unsigned long long id);
        bool isPlayerAlive();
        bool playerWin();

    protected:
    private:
        Instance _instance;
        std::vector<Entity *> _entities;
        Storage<Position> _positionStorage;
        Storage<Velocity> _velocityStorage;
        Storage<Collider> _colliderStorage;
        Storage<Tag> _typeStorage;
        Storage<Clock> _clockStorage;
        Storage<Collectible> _collectibleStorage;
        Storage<Shooting> _shootingStorage;
        Storage<Playable> _playableStorage;
        MovementSystem _movementSystem;
        InputSystem _inputSystem;
        CollisionSystem _collisionSystem;
        FloorSystem _floorSystem;
        ClockSystem _clockSystem;
        CollectibleSystem _collectibleSystem;
        ShootingSystem _shootingSystem;
        Storage<Walkable> _walkableStorage;
        int _score;
};

#endif /* !LIBSOLAR_HPP_ */