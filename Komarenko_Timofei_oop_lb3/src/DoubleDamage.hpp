#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H
#include "Ability.hpp"
#include "GameMap.hpp"


class DoubleDamage : public Ability{
private:
    AbilityManager* manager;
public:
    DoubleDamage(AbilityManager* manager);

    void use() override;
};


#endif