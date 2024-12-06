#ifndef SCANER_H
#define SCANER_H
#include "Ability.hpp"

class Scanner : public Ability{
private:
    GameMap* field;
    bool employment;
    int x,y;
public:
    Scanner(GameMap* field);

    void use() override;

    void setCoord(int x, int y) override;

};

#endif