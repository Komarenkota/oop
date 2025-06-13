#ifndef SEGMENT_H
#define SEGMENT_H

class Ship;

class Segment{
public:
    Segment() : condition(Undamaged){}
    void Attack();
    enum Condition{
        Undamaged = 2,
        Damaged = 1,
        Destroyed = 0
    };
    Segment::Condition GetCondition() const;

    void setCondition(int newCond);

    void setConditionToDestroy();

private:
    Condition condition = Condition::Undamaged;
};


#endif