#include "GameMap.hpp" 
#include "Exceptions.hpp"
#include "AbilityManager.hpp"

GameMap::GameMap(size_t side) : side(side){
    this->side = side;

    this->map = new Cell*[side];
    for (size_t i = 0; i < side; ++i)
        this->map[i] = new Cell[side]();
}

GameMap::GameMap(const GameMap& source){
    this->side = source.side;
    this->map = new Cell*[this->side];
    for (size_t i = 0; i < this->side; ++i){
        this->map[i] = new Cell[this->side];
        for (size_t j = 0; j < this->side; ++j)
            this->map[i][j] = source.map[i][j];
    }
}

GameMap& GameMap::operator=(const GameMap& source) {
    if (this != &source) {

        if (this->map) {
            for (size_t i = 0; i < this->side; ++i)
                delete[] this->map[i];
            delete[] this->map;
        }


        this->side = source.side;
        this->map = new Cell*[this->side];
        for (size_t i = 0; i < this->side; ++i) {
            this->map[i] = new Cell[this->side];
            for (size_t j = 0; j < this->side; ++j) {
                this->map[i][j] = source.map[i][j];
            }
        }
    }
    return *this;
}

GameMap::GameMap(GameMap&& source){
    this->side = source.side;
    this->map = source.map;

    source.side = 0;
    source.map = nullptr;
}

GameMap& GameMap::operator=(GameMap&& source){
    if (this != &source){
        if (this->map){
            for (size_t i = 0; i < side; ++i)
                delete[] map[i];
            delete[] map;
        }

        this->side = source.side;
        this->map = source.map;

        source.side = 0;
        source.map = nullptr;
    }
    return *this;
}

void GameMap::TakeShip(const std::vector<int>& Coord, Ship* ship, int shipIndex) {
    int x = Coord[0] - 1;
    int y = Coord[1] - 1;

    bool canPlace = true;

    auto isValid = [&](size_t row, size_t col) -> bool {
        return row >= 0 && row < this->side && col >= 0 && col < this->side;
    };

    auto checkNeighbors = [&](int row, int col) -> bool {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newRow = row + i;
                int newCol = col + j;
                if (isValid(newRow, newCol) && map[newRow][newCol].GetStatus() == Cell::ship_present) {
                    return false;
                }
            }
        }
        return true;
    };

    if (ship->GetOrientation() == Ship::Orientation::Vert) {
        if (x + ship->GetLength() <= int(this->side) && y < int(this->side)) {
            for (int i = 0; i < ship->GetLength(); ++i) {
                if (map[x + i][y].GetStatus() == Cell::ship_present || !checkNeighbors(x + i, y)) {
                    canPlace = false;
                    break;
                }
            }
            if (canPlace) {
                for (int i = 0; i < ship->GetLength(); ++i) {
                    map[x + i][y].setSegment(ship->GetPtrSeg(i));
                    map[x + i][y].SetStatus(Cell::ship_present);
                }
            } else {
                throw incorrectShipPosition();
            }
        } else {
            throw outOfFieldPosition();
        }
    } else if (ship->GetOrientation() == Ship::Orientation::Hori) {
        if (y + ship->GetLength() <= int(this->side) && x < int(this->side)) {
            for (int i = 0; i < ship->GetLength(); ++i) {
                if (map[x][y + i].GetStatus() == Cell::ship_present || !checkNeighbors(x, y + i)) {
                    canPlace = false;
                    break;
                }
            }
            if (canPlace) {
                for (int i = 0; i < ship->GetLength(); ++i) {
                    map[x][y + i].setSegment(ship->GetPtrSeg(i));
                    map[x][y + i].SetStatus(Cell::ship_present);
                }
            } else {
                throw incorrectShipPosition();
            }
        } else {
            throw outOfFieldPosition();
        }
    } else {
        std::cout << "Неверная ориентация корабля!" << std::endl;
    }
}

Cell& GameMap::GetCell(int x, int y){
    return this->map[x][y];
}

int GameMap::GetSide(){
    return this->side;
}

void GameMap::AttackCell(int x, int y) {
    --x;
    --y;

    if (x >= 0 && x < int(side) && y >= 0 && y < int(side)) {
        std::cout << "Hit! (" << x + 1 << ", " << y + 1 << ")\n";
        map[x][y].AttackShip();
    } else {
        throw outOfFieldAttack();
    }
}



void GameMap::DoubleDamageAttack(int x, int y){
    --x;
    --y;
    if (x >= 0 && x < int(side) && y >= 0 && y < int(side)) {
        std::cout << "Hit! (" << x + 1 << ", " << y + 1 << ")\n";
        map[x][y].DoubleAttackShip();
    } else {
        throw outOfFieldAttack();
    }
}

void GameMap::setCellsHidden(){
    for (size_t y = 0; y < this->side; ++y){
        for (size_t x = 0; x < this->side; ++x){
            map[x][y].SetStatus(Cell::unknown);
        }
    }
}

void GameMap::PrintStat(){
    for (size_t y = 0; y < this->side; ++y){
        for (size_t x = 0; x < this->side; ++x){
            if (this->map[y][x].GetStatus() ==  Cell::empty){
                std::cout<<"□"<<' ';
            }else if(this->map[y][x].GetStatus() ==  Cell::ship_present){
                Segment* segment = &this->map[y][x].GetSegment();
                if(segment != nullptr){
                    switch (segment->GetCondition()){
                        case Segment::Condition::Undamaged:
                            std::cout<<2<<" ";
                            break;
                        case Segment::Condition::Damaged:
                            std::cout<<1<<" ";
                            break;
                        default:
                            std::cout<<"x"<<" ";
                    }
                }
            }else{
                std::cout<<"?"<<' ';
            }
        }
        std::cout<<std::endl;
    }
}



GameMap::~GameMap(){
    if (this->map){
        for (size_t i = 0; i < this->side; ++i)
            delete [] this->map[i];
        delete [] this->map;
    }
}