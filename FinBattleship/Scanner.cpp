#include "Scanner.hpp"

Scanner::Scanner(GameMap* field): field(field), employment(false){}

void Scanner::use(){
    int x,y;
    std::cout<<"Введите начальные координаты сконирования:"<<'\n';
    std::cin >> x >> y;
    setCoord(x,y);
    for(int i = x - 1; i < x+1; i++){
        for(int j = y - 1; j < y+1; j++){
            if(i < field->GetSide() && j < field->GetSide()){
                if(field->GetCell(i,j).checkSeg()){
                    employment = true;
                }
            }else{
                std::cout << "Вышли за поле!!!" << '\n';
            }
        }
    }
    if(employment){
        std::cout << "На этом участке есть сегмент корабля!!!" << '\n';
    }else{
        std::cout << "На этом участке нет сегмента корабля!!!" << '\n';
    }
}

void Scanner::setCoord(int x, int y){
    this->x = x;
    this->y = y;
}