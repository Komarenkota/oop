#ifndef FILEWRAPPER_H
#define FILEWRAPPER_H

#include "GameState.hpp"
#include <fstream>
#include <stdexcept>

class FileWrapper {
    std::fstream file;

public:
    FileWrapper(const std::string& fileName, std::ios::openmode mode);

    void saveToFile(GameState* gameState);

    void loadFromFile(GameState* gameState);

    ~FileWrapper();
};

#endif
