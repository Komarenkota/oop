#include "Shelling.hpp"

Shelling::Shelling(GameMap* field): field(field){
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Shelling::use() {
    int side = field->GetSide();
    std::vector<Cell*> aliveSegments;

    for(int j = 0; j < side; j++)
        for(int i = 0; i < side; i++){
            if(field->GetCell(i,j).checkSeg()){
                aliveSegments.emplace_back(&field->GetCell(i,j)); 
            }
        }

    if (aliveSegments.empty()) {
        std::cerr << "Ошибка: Все сегменты у всех кораблей уничтожены.\n";
        return;
    }

    int randomAliveIndex = std::rand() % aliveSegments.size();
    Cell* targetCell = aliveSegments[randomAliveIndex];
    
    targetCell->AttackShip();
}

