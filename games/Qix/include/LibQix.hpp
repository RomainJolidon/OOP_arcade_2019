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
#include "../ECS/include/ClockSystem.hpp"
#include "../ECS/include/PathSystem.hpp"

class LibQix: public IGameModule {
    public:
    LibQix();
    void receiveEvent(KeyBind key) override ;
    const std::vector<Entity *> &getEntities() override ;
    bool oneCycleLoop() override ;
    int getScore() const override ;
    ~LibQix() override;

    protected:
    private:

    void initAllEntities();
    void destroyAllEntities();
    void resetGame();
    void addFloor(int x, int y);
    void addWall(int x, int y);
    void initBordervector(int xStatr, int yStart);
    void getSurface();
    std::pair<int, int> getRandomBorderPos() const;
    std::vector<std::pair<int, int>>::iterator getBorderIteratorMatching(int x, int y);
    void fillSurface(const std::vector<std::pair<int, int>>& surfaceBorder);
    int getLeftPositionAtLine(int y, const std::vector<std::pair<int, int>>& surfaceBorder) const;
    int getTopPositionAtLine(int x, const std::vector<std::pair<int, int>>& surfaceBorder) const;
    int getBottomPositionAtLine(int x, const std::vector<std::pair<int, int>>& surfaceBorder) const;
    int getRightPositionAtLine(int y, const std::vector<std::pair<int, int>>& surfaceBorder) const;
    int getTopPosition(const std::vector<std::pair<int, int>>& surfaceBorder) const;
    int getBottomPosition(const std::vector<std::pair<int, int>>& surfaceBorder) const;
    bool isInSurfaceAtLine(int x, int y, const std::vector<std::pair<int, int>>& surfaceBorder) const;

    Instance _instance;
    Storage<Velocity> _velocityStorage;
    Storage<Position> _positionStorage;
    Storage<Collider> _colliderStorage;
    Storage<Tag> _typeStorage;
    Storage<AI> _AIStorage;
    AISystem _AISystem;
    Storage<Playable> _playableStorage;
    Storage<Walkable> _walkableStorage;
    Storage<Clock> _clockStorage;
    Storage<Collectible> _collectibleStorage;
    MovementSystem _movementSystem;
    InputSystem _inputSystem;
    CollisionSystem _collisionSystem;
    FloorSystem _floorSystem;
    ClockSystem _clockSystem;
    Storage<Path> _pathStorage;
    PathSystem _pathSystem;
    std::vector<Entity *> _entities;

    std::vector<std::pair<int, int>> _borderVector;


    int _score;
    int _nbEnnemies;

};

#endif //OOP_ARCADE_2019_LIBNIBBLER_HPP
