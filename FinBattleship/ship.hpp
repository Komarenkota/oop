#ifndef SHIP_H
#define SHIP_H

#include <vector>  
#include <iostream>
#include <string>
#include "Segment.hpp"

class Manager;

class Ship {
public:
    enum Orientation{Hori = 0, Vert = 1};

    Ship(int length,Orientation orientation);

    Ship(int length);

    void SetOri(Ship::Orientation ori);

    int GetLength() const ;

    Ship::Orientation GetOrientation() const ;

    void PrintHealth();

    std::vector<Segment>& getSegments();

    Segment& GetPtrSeg(int index);

    bool isSunk();

private:
    bool sunked;
    int length;
    Orientation orientation;
    std::vector<Segment> segments; 
};


#endif 