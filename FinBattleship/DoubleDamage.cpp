#include "DoubleDamage.hpp"
#include "AbilityManager.hpp"

DoubleDamage::DoubleDamage(AbilityManager* manager): manager(manager){
}

void DoubleDamage::use(){
    manager->setMarkOfDoubledamage();
}
