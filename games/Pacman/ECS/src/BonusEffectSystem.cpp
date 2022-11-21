/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#include "../include/BonusEffectSystem.hpp"

BonusEffectSystem::BonusEffectSystem()
{
}

BonusEffectSystem::~BonusEffectSystem()
{
}

int BonusEffectSystem::update(
    Storage <Playable> *playableStorage,
    Storage <AI> *AIStorage,
    Storage <Bonus> *bonusStorage,
    Storage <Tag> *typeStorage,
    int score
    ) const
{
    for (auto it : playableStorage->entityIdxToComponentIdxMap) {
        score = process(playableStorage, AIStorage, bonusStorage, typeStorage, score, it.first);
    }
    return score;
}

int BonusEffectSystem::process(
    Storage <Playable> *playableStorage,
    Storage <AI> *AIStorage,
    Storage <Bonus> *bonusStorage,
    Storage <Tag> *typeStorage,
    int score,
    unsigned long long int entityID
) const
{
    static bool superBonusIsActive = false;
    static unsigned long long int treshold = 0;
    Effect playerEffect = playableStorage->getComponentForEntity(
        entityID).effect;

    treshold++;
    if (superBonusIsActive && (treshold >= 100)) {
        for (auto it : AIStorage->entityIdxToComponentIdxMap) {
            typeStorage->getComponentForEntity(it.first).type = ENEMY_1;
            if (bonusStorage->hasEntityComponent(it.first))
                bonusStorage->removeComponentForEntity(it.first);
        }
        treshold = 0;
        superBonusIsActive = false;
    }
    switch (playerEffect) {
    case BONUS1:
        score++;
        playableStorage->getComponentForEntity(entityID).effect = NOEFFECT;
        break;
    case SUPERBONUS1:
        for (auto it : AIStorage->entityIdxToComponentIdxMap) {
            typeStorage->getComponentForEntity(it.first).type = ENEMY_3;
            if (!bonusStorage->hasEntityComponent(it.first)) {
                bonusStorage->addComponentForEntity(it.first);
                bonusStorage->getComponentForEntity(it.first) = Bonus{it.first,
                    SUPERBONUS2};
            }
        }
        superBonusIsActive = true;
        treshold = 0;
        score += 500;
        playableStorage->getComponentForEntity(entityID).effect = NOEFFECT;
        break;
    case SUPERBONUS2:
        score += 1000;
        playableStorage->getComponentForEntity(entityID).effect = NOEFFECT;
        break;
    default:
        break;
    }
    return score;
}
