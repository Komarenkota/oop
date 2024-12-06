#ifndef ABILITY_H
#define ABILITY_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "GameMap.hpp"

class Ability {
public:
    virtual void use() = 0;
    virtual void setCoord(int x, int y){
    }
    virtual ~Ability() = default;
};

#endif
