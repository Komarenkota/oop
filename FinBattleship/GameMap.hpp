#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "Cell.hpp"

class AbilityManager;

class GameMap {
private:
    Cell** map;
    size_t side;

public:

    GameMap(size_t side);

    GameMap(const GameMap& source);

    GameMap& operator=(const GameMap& source);
    
    GameMap(GameMap&& source);

    GameMap& operator=(GameMap&& source);

    Cell& GetCell(int x, int y);

    int GetSide();

    void TakeShip(const std::vector<int>& Coord, Ship* ship, int shipIndex);

    void setCellsHidden();
    
    void AttackCell(int x, int y);

    void DoubleDamageAttack(int x, int y);

    ~GameMap();
};

#endif