#include <iostream>
#include "Cell.hpp"
#include "Manager.hpp"
#include "ship.hpp"

Cell::Cell() : segment(nullptr), cellStatus(empty) {}


Cell& Cell::operator=(const Cell& other) {
        if (this != &other) { 
           delete this->segment;

            if (other.segment) {
                this->segment = new Segment(*other.segment); 
            } else {
                this->segment = nullptr;
            }

            this->cellStatus = other.cellStatus;
        }
        return *this;
}

void Cell::setSegment(Segment& segment){
    this->segment = &segment;
}

void Cell::AttackShip() {
    if (segment) {
        segment->Attack();
        cellStatus = ship_present;
    }else{
        cellStatus = empty;
    }
}

void Cell::DoubleAttackShip() {
    if (segment) {
        segment->setConditionToDestroy();
        cellStatus = ship_present;
    }else{
        cellStatus = empty;
    }
}

Cell::Status Cell::GetStatus() const{
    return this->cellStatus;
}

void Cell::SetStatus(Status newStatus){
    this->cellStatus = newStatus;
}

bool Cell::checkSeg() const {
    if(segment == nullptr){
        return false;
    }
    return true;
}

Segment& Cell::GetSegment()const {
    return *this->segment;
}

Cell::~Cell() {
}