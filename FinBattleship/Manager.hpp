#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> 
#include "ship.hpp"

class AbilityManager;

class Manager {
private:
    std::vector<Ship> ships;
    size_t countShips; 
    size_t countAliveShips; 

public:
    Manager() = default;

    Manager(std::vector<int> ship_lens);

    Manager(std::vector<int> ship_lens, int count);

    Ship& operator[](size_t index);

    void AddShip(Ship ship);

    std::vector<Ship>& getShips();

    bool checkNewSunk();

    bool checkAllSunk() const ; 
};

#endif