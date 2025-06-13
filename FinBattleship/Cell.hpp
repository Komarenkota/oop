#ifndef CELL_H
#define CELL_H
#include <memory>
#include "ship.hpp"

class Cell {
public:
    Cell();
    void AttackShip();
    void DoubleAttackShip();
    enum Status{
        unknown = 0,
        empty = 1,        
        ship_present = 2
    };
    void SetStatus(Status NewStatus);
    Status GetStatus() const;
    Segment& GetSegment() const;
    bool checkSeg() const;
    void setSegment(Segment& segment);
    Cell& operator=(const Cell& other);
    ~Cell();
private:
    Segment* segment; 
    Status cellStatus = empty;
};

#endif