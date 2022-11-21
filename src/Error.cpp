/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Error
*/

#include "Error.hpp"

Error::ArcadeError::ArcadeError(std::string const &message, std::string const &type)
: _message(message), _type(type), _printable(type + ": " + message + "\n") {}

const std::string &Error::ArcadeError::getType() const {
    return _type;
}

const char *Error::ArcadeError::what() const throw() {
    return _printable.c_str();
}

Error::CoreError::CoreError(std::string const &message)
: Error::ArcadeError(message, "core_error") {};

Error::GameError::GameError(std::string const &message)
: Error::ArcadeError(message, "game_error") {};

Error::GraphError::GraphError(std::string const &message)
: Error::ArcadeError(message, "graph_error") {};