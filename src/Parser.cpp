/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "Parser.hpp"

std::list<std::string> Parser::parseMap(const std::string &filepath, int top, int left)
{
    std::ifstream fd;
    std::string line;
    std::list<std::string> map;

    fd.open(filepath);
    if (!fd.is_open()) {
        return (map);
    }
    while (std::getline(fd, line)) {
        map.push_back(line);
    }
    fd.close();
    _top = top;
    _left= left;
    _width = map.begin()->size();
    _height = map.size();
    return (map);
}

int Parser::getTop()
{
    return (_top);
}

int Parser::getLeft()
{
    return (_left);
}

int Parser::getWidth()
{
    return (_width);
}

int Parser::getHeight()
{
    return (_height);
}

std::string Parser::getLibName(const std::string& lib)
{
    return (lib.substr(0, lib.find('.')));
}

std::string Parser::getLibPath(const std::string &lib, const std::string &path)
{
    return (std::string(path + lib));
}

bool Parser::endWith(const std::string &str, const std::string &end)
{
    if (end.size() > str.size())
        return false;
    return std::equal(end.rbegin(), end.rend(), str.rbegin());
}

bool Parser::startWith(const std::string &str, const std::string &start)
{
    if (start.size() > str.size())
        return false;
    return (str.rfind(start, 0) == 0);
}

bool Parser::isFileExists(const std::string &filepath)
{
    std::ifstream fd;

    fd.open(filepath);
    if (!fd.is_open())
        return (false);
    fd.close();
    return true;
}

bool Parser::isDirExists(const std::string &filepath)
{
    DIR *dir = opendir(filepath.c_str());

    if (!dir)
        return (false);
    closedir(dir);
    return (true);
}

bool Parser::checkArgs(int ac, char **av)
{
    if (ac != 2)
        return (false);
    if (std::string(av[1]) == "-h" || std::string(av[1]) == "--help") {
        std::cout
            << "USAGE: ./arcade ./lib/lib_name.so" << std::endl;
        std::cout << "the graphical library has to be in the `./lib` folder" << std::endl;
        std::cout << "don't forget the './' before the lib path !"
            << std::endl;
        return (false);
    }
    if (!endWith(av[1], ".so") || !startWith(av[1], "./lib/"))
        return (false);
    else if (!isFileExists(av[1]))
        return (false);
    return (true);
}

int Parser::_top = 0;
int Parser::_left = 0;
int Parser::_width = 0;
int Parser::_height = 0;

DIR *Parser::openDir(const std::string &filepath)
{
    DIR *dir = opendir(filepath.c_str());
    if (!dir)
        return (nullptr);
    return (dir);
}

void Parser::closeDir(DIR *dir)
{
    if (dir)
        closedir(dir);
}

bool Parser::createDir(const std::string &filepath, int mode)
{
    return (mkdir(filepath.c_str(), mode) != -1);
}

std::string Parser::readDirOnce(DIR *dir, const std::string& ext)
{
    struct dirent *data;

    if (!dir) {
        return ("");
    }
    if ((data = readdir(dir)) != nullptr) {
        if (endWith(data->d_name, ext)) {
            return (data->d_name);
        } else {
            return ("");
        }
    }
    return ("end");
}
