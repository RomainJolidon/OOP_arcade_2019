/*CollisionSystem
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_BONUSEFFECTSYSTEM_HPP
#define OOP_ARCADE_2019_BONUSEFFECTSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class BonusEffectSystem {
    public:
    BonusEffectSystem();
    ~BonusEffectSystem();
    int update(
        Storage <Playable> *playableStorage,
        Storage <AI> *AIStorage,
        Storage <Bonus> *bonusStorage,
        Storage <Tag> *typeStorage,
        int score) const;
    protected:
    private:
    int process(
        Storage <Playable> *playableStorage,
        Storage <AI> *AIStorage,
        Storage <Bonus> *bonusStorage,
        Storage <Tag> *typeStorage,
        int score,
        unsigned long long int entityID) const;
};

#endif //OOP_ARCADE_2019_BONUSEFFECTSYSTEM_HPP
