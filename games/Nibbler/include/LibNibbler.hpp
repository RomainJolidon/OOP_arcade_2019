/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_LIBNIBBLER_HPP
#define OOP_ARCADE_2019_LIBNIBBLER_HPP

#include <chrono>
#include "IGameModule.hpp"
#include "Parser.hpp"
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
#include "../ECS/include/ClockSystem.hpp"

class LibNibbler: public IGameModule {
    public:
    LibNibbler();
    void receiveEvent(KeyBind key) override ;
    const std::vector<Entity *> &getEntities() override ;
    bool oneCycleLoop() override ;
    int getScore() const override ;
    ~LibNibbler() override;

    protected:
    private:

    void addFloor(int x, int y);
    void addWall(int x, int y);
    void addBonus(int x, int y);
    unsigned long long int addFollower(unsigned long long int targetId);
    void addRandomBonus();

    Instance _instance;
    Storage<Velocity> _velocityStorage;
    Storage<Position> _positionStorage;
    Storage<Collider> _colliderStorage;
    Storage<Follower> _followerStorage;
    Storage<Tag> _typeStorage;
    Storage<Playable> _playableStorage;
    Storage<Walkable> _walkableStorage;
    Storage<Clock> _clockStorage;
    Storage<Collectible> _collectibleStorage;
    MovementSystem _movementSystem;
    InputSystem _inputSystem;
    CollisionSystem _collisionSystem;
    CollectibleSystem _collectibleSystem;
    FollowerSystem _followerSystem;
    FloorSystem _floorSystem;
    ClockSystem _clockSystem;
    std::vector<Entity *> _entities;

    unsigned long long int _targetId;

    int _score;

};

#endif //OOP_ARCADE_2019_LIBNIBBLER_HPP
