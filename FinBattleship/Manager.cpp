#include "Manager.hpp" 

Manager::Manager(std::vector<int> ship_lens){
    this->countShips = ship_lens.size();
    this->countAliveShips = countShips;
    for (auto ship_len: ship_lens)
        this->ships.push_back(Ship(ship_len));
}

Manager::Manager(std::vector<int> ship_lens, int count){
    this->countShips = count;
    this->countAliveShips = countShips;
    for (auto ship_len: ship_lens)
        this->ships.push_back(Ship(ship_len));
}

void Manager::AddShip(Ship ship) {
    ships.push_back(ship);
}

std::vector<Ship>& Manager::getShips(){
    return ships;
}

bool Manager::checkNewSunk(){
    for (Ship& ship : ships) {
            if (ship.isSunk()) {
                countAliveShips -= 1;
                return true;
            }
    }
    return false;
}


Ship& Manager::operator[](size_t index){
    return this->ships.at(index);
}

bool Manager::checkAllSunk() const {
    if(countAliveShips<1){
        return true;
    }else{
        return false;
    }
}