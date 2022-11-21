/*
** EPITECH PROJECT, 2020
** Arcade Bootstrap
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

template <typename T>
DLLoader<T>::DLLoader(const std::string &libPath) try {
    this->_handler = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!this->_handler)
        throw std::exception();
} catch (std::exception &e) {
    std::cerr << e.what();
}

template <typename T>
DLLoader<T>::~DLLoader() {
    dlclose(this->_handler);
    std::cout << "Unloading Library" << std::endl;
}

template <typename T>
T *DLLoader<T>::getInstance(const std::string &functionPath) {
    T *(*ctopPtr)();

    ctopPtr = reinterpret_cast<T *(*)()>(dlsym(this->_handler, functionPath.c_str()));
    return ctopPtr();
}