#include "FileWrapper.hpp"


FileWrapper::FileWrapper(const std::string& fileName, std::ios::openmode mode)
    : file(fileName, mode)
{
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }
}


void FileWrapper::saveToFile(GameState* gameState) {
    file << (*gameState); 
}


void FileWrapper::loadFromFile(GameState* gameState) {
    file >> (*gameState);
}

FileWrapper::~FileWrapper() {
    if (file.is_open()) {
        file.close();
    }
}
