/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_INPUTSYSTEM_HPP
#define OOP_ARCADE_2019_INPUTSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class InputSystem {
        public:
        InputSystem();
        ~InputSystem();
        void update(Storage<Playable> *playableStorage, Storage<Path> *pathStorage,  Storage<Velocity> *velocityStorage, KeyBind key) const;
        protected:
        private:
        void process(Storage<Playable> *playableStorage, Storage<Path> *pathStorage, Storage<Velocity> *velocityStorage, unsigned long long int entityID, KeyBind key) const;
};

#endif //OOP_ARCADE_2019_INPUTSYSTEM_HPP
