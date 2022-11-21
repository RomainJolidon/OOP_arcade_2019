/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#ifndef OOP_ARCADE_2019_PARSER_HPP
#define OOP_ARCADE_2019_PARSER_HPP

#include <list>
#include <string>
#include <fstream>
#include <dirent.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_map>

#include "Error.hpp"
#include "DLLoader.hpp"

class Parser {
    public:
    Parser() = default;

    ~Parser() = default;
    static std::list<std::string> parseMap(const std::string& filepath, int top, int left);
    static int getTop() ;
    static int getLeft() ;
    static int getWidth();
    static int getHeight() ;
    static std::string getLibName(const std::string &lib);
    static std::string getLibPath(const std::string &lib,const std::string &path);
    static bool endWith(const std::string &str, const std::string &end);
    static bool startWith(const std::string &str, const std::string &start);
    static bool isFileExists(const std::string& filepath);
    static bool isDirExists(const std::string& filepath);
    static bool createDir(const std::string& filepath, int mode);
    static DIR *openDir(const std::string& filepath);
    static void closeDir(DIR *dir);
    template <typename T>
    static std::unordered_map<std::string, DLLoader<T> *> readDirLib(DIR *dir, const std::string& libPath, const std::string& ext);
    template <typename T>
    static DLLoader<T> *loadLib(std::string& filepath, const std::string& libPath);
    static std::string readDirOnce(DIR *dir, const std::string& ext);
    static bool checkArgs(int ac, char **av);

    static int _top;
    static int _left;
    static int _width;
    static int _height;
    protected:
    private:
};

template <typename T>
std::unordered_map<std::string, DLLoader<T> *> Parser::readDirLib(DIR *dir, const std::string& libPath, const std::string& ext) {
    std::unordered_map<std::string, DLLoader<T> *> map;
    struct dirent *data;
    std::string name;

    while ((data = readdir(dir)) != nullptr) {
        if (endWith(data->d_name, ext)) {
            name = data->d_name;
            try {
                map[getLibPath(name, libPath)] = loadLib<T>(name, libPath);
            } catch(const Error::CoreError& e) {
                throw e;
            }
        }
    }
    return (map);
}

template <typename T>
DLLoader<T> *Parser::loadLib(std::string& filepath, const std::string& libPath)
{
    DLLoader<T> *dlLoader = nullptr;
    try {
        dlLoader = new DLLoader<T>(Parser::getLibPath(filepath, libPath));
    } catch (const std::exception& e) {
        throw Error::CoreError("Failed to open library: " + filepath + " in file " + libPath + ": " + dlerror());
    }
    filepath = Parser::getLibName(filepath);
    std::cout << "[" << filepath << "]: loading " << filepath << " library..." << std::endl;

    return (dlLoader);
}

#endif //OOP_ARCADE_2019_PARSER_HPP
