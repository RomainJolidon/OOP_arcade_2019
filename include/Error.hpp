/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>

namespace Error {
    class ArcadeError: public std::exception {
        public:
            ArcadeError(std::string const &message, std::string const &type);
            ~ArcadeError() = default;
            const std::string &getType() const;
            const char *what() const throw();
        private:
            std::string _message;
            std::string _type;
            std::string _printable;
    };

    class CoreError : public ArcadeError {
        public:
            CoreError(std::string const &message);
    };

    class GameError : public ArcadeError {
        public:
            GameError(std::string const &message);
    };

    class GraphError : public ArcadeError {
        public:
            GraphError(std::string const &message);
    };
};

#endif /* !ERROR_HPP_ */