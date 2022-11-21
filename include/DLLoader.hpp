/*
** EPITECH PROJECT, 2020
** Arcade Bootstrap
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <string>

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

template <typename T>
class DLLoader {
    public:
        DLLoader(const std::string &libPath);
        ~DLLoader();
        T *getInstance(const std::string &functionPath);

    private:
        void *_handler;
};

template class DLLoader<IDisplayModule>;
template class DLLoader<IGameModule>;

#endif /* !DLLOADER_HPP_ */