#ifndef ABILITY_MANAGER_HPP
#define ABILITY_MANAGER_HPP

#include <queue>
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "Ability.hpp"
#include "DoubleDamage.hpp"
#include "Scanner.hpp"
#include "Shelling.hpp"

class AbilityManager {
private:
    GameMap* field;
    std::queue<Ability*> abilitiQueue;
    bool markOfDoubleDamage;

public:
    AbilityManager();

    AbilityManager( GameMap* field);

    size_t getLenQueue();

    void useAbility();

    void setField(GameMap* field);

    void setMarkOfDoubledamage();

    void addRandomAbility();

    bool isDoubleDamageActive() const;

    void resetDoubleDamage();
};

#endif