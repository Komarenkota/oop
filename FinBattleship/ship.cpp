#include "ship.hpp" 

Ship::Ship(int length,Orientation orientation) :sunked(false), length(length), orientation(orientation){
    segments.resize(length);
}

Ship::Ship(int length) : sunked(false), length(length){
    segments.resize(length);
}

void Ship::SetOri(Ship::Orientation ori){
    this->orientation = ori;    
}

int Ship::GetLength() const { return length; }


Ship::Orientation Ship::GetOrientation() const {
    return this->orientation;
}


void Ship::PrintHealth() {
    for (auto h : segments) {
        std::cout << h.GetCondition();
    }
    std::cout << '\n';
}

std::vector<Segment>& Ship::getSegments(){
    return segments;
}

Segment& Ship::GetPtrSeg(int index){
    return segments.at(index);
}

bool Ship::isSunk() {
    if (sunked) {
        return false; 
    }
    
    for (auto& segment : segments) {
        if (segment.GetCondition() == Segment::Condition::Undamaged || 
            segment.GetCondition() == Segment::Condition::Damaged) {
            return false;
        }
    }
    sunked = true;
    return true;
}