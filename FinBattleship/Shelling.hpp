#ifndef SHELLING_H
#define SHELLING_H
#include "Ability.hpp"
#include <cstdlib> 
#include <ctime>

class Shelling: public Ability{
private:
    GameMap* field;
public:
    Shelling(GameMap* field);

    void use() override;
};

#endif