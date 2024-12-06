#include <iostream>
#include "Segment.hpp" 

Segment::Condition Segment::GetCondition() const{
    return condition;
}


void Segment::Attack(){
    if (condition == Condition::Undamaged){
        condition = Damaged;
    }else if (condition == Condition::Damaged)
        condition = Destroyed;
}

void Segment::setCondition(int newCondition){
    if(newCondition == 0){    
        condition = Segment::Condition::Destroyed;
    }else if(newCondition == 1){
        condition = Segment::Condition::Damaged;
    }else{
        condition = Segment::Condition::Undamaged;
    }
}


void Segment::setConditionToDestroy(){
    condition = Destroyed;
}
