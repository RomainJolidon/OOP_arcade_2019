/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_PACMAN_HPP
#define OOP_ARCADE_2019_PACMAN_HPP

#include <unordered_map>
#include <chrono>
#include "IGameModule.hpp"
#include "../ECS/include/Components.hpp"
#include "../ECS/include/Instance.hpp"
#include "../ECS/include/MovementSystem.hpp"
#include "../ECS/include/Storage.hpp"
#include "../ECS/include/InputSystem.hpp"
#include "../ECS/include/CollisionSystem.hpp"
#include "../ECS/include/AiSystem.hpp"
#include "../ECS/include/BonusEffectSystem.hpp"
#include "../ECS/include/ClockSystem.hpp"
#include "../ECS/include/ClockSystem.hpp"

class Pacman: public IGameModule {
    public:
    explicit Pacman();
    ~Pacman() override;
    void receiveEvent(KeyBind key) override;
    const std::vector<Entity *> &getEntities() override;
    bool oneCycleLoop() override;
    int getScore() const override;
    void createWallAtPosition (int x, int y);
    void createFloorAtPosition (int x, int y);
    void createBonusAtPosition (int x, int y, Effect effect, TypeEntity bonusType);
    void createAllEntities();
    void emptyAllEntities();
    void resetGame();
    protected:
    private:
    Instance _instance;
    Storage<Velocity> _velocityStorage;
    Storage<Position> _positionStorage;
    Storage<Collider> _colliderStorage;
    Storage<Tag> _typeStorage;
    Storage<Playable> _playableStorage;
    Storage<Clock> _clockStorage;
    Storage<AI> _AIStorage;
    Storage<Bonus> _bonusStorage;
    MovementSystem _movementSystem;
    InputSystem _inputSystem;
    CollisionSystem _collisionSystem;
    AISystem _AISystem;
    BonusEffectSystem _bonusEffectSystem;
    ClockSystem _clockSystem;
    std::vector<Entity *> _entities;
    KeyBind _input;
    int _gameSpeed;
    int _score;
};

#endif //OOP_ARCADE_2019_PACMAN_HPP
