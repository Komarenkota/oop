#include "AbilityManager.hpp"
#include <iostream>
#include "Exceptions.hpp"

AbilityManager::AbilityManager(){
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    this->markOfDoubleDamage = false;
}


AbilityManager::AbilityManager(GameMap* field):field(field) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    this->markOfDoubleDamage = false;
    addRandomAbility();
}

size_t AbilityManager::getLenQueue(){
    return int(abilitiQueue.size());
}


void AbilityManager::setField(GameMap* field){
    this->field = field;
}

void AbilityManager::useAbility() {
    if (abilitiQueue.empty()) {
        throw noAbilities();
    }
    
    Ability* ability = abilitiQueue.front();
    abilitiQueue.pop();
    ability->use();
}

void AbilityManager::setMarkOfDoubledamage(){
    this->markOfDoubleDamage = true;
}

bool AbilityManager::isDoubleDamageActive() const{
    return this->markOfDoubleDamage;
}

void AbilityManager::resetDoubleDamage(){
    this->markOfDoubleDamage = false;
}

void AbilityManager::addRandomAbility() {
    if (field == nullptr) {
        return;
    }
    int randomAbility = std::rand() % 3;
    switch (randomAbility) {
        case 0:
            abilitiQueue.push(new Scanner(field));
            break;
        case 1:
            abilitiQueue.push(new Shelling(field));
            break;
        case 2:
            abilitiQueue.push(new DoubleDamage(this));
            break;
    }
}