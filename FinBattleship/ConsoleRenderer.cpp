#include "ConsoleRenderer.hpp"
#include "GameMap.hpp"
#include "Segment.hpp"
#include <stdlib.h>


void ConsoleRenderer::renderState(GameState& state){
    std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
    
    std::cout<<"Count of abilities:"<<state.getAbilManager()->getLenQueue()<<'\n';
    std::cout<<"Phase of game:"<<state.getPhase()<<'\n';

    size_t side = state.getUserField()->GetSide();

    for (size_t x = 0; x < side; ++x){
        for (size_t y = 0; y < side; ++y){
            if (state.getUserField()->GetCell(x,y).GetStatus() ==  Cell::empty){
                std::cout<<"□"<<' ';
            }else if(state.getUserField()->GetCell(x,y).GetStatus() ==  Cell::ship_present){
                Segment* segment = &(state.getUserField()->GetCell(x,y).GetSegment());
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

    std::cout<<std::endl;

    for (size_t x = 0; x< side; ++x){
        for (size_t y = 0; y < side; ++y){
            if (state.getEnemyField()->GetCell(x,y).GetStatus() ==  Cell::empty){
                std::cout<<"□"<<' ';
            }else if(state.getEnemyField()->GetCell(x,y).GetStatus() ==  Cell::ship_present){
                Segment* segment = &(state.getEnemyField()->GetCell(x,y).GetSegment());
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
    std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
}


void ConsoleRenderer::clearConsole(){
        std::system("clear");
}


void ConsoleRenderer::unknownCommand(){
        std::cout<<"Command :"<<" is not found!"<< '\n';
}


void ConsoleRenderer::unknownOri(){
    std::cout<<"Unknown Orientation!!!\n Can be: v(verticall) or h(horizontal)"<< '\n';
}


void ConsoleRenderer::inCorrectPhase(){
    std::cout<<"In this phase you can`t use it command!!!\n For (0) phase: PlaseShip or Load\n For (1) phase: Fair, Save, Load, useAbil "<< '\n';
}


void ConsoleRenderer::inCorrectArgs(){
    std::cout<<"Incorrect args for this command!!!\n PlaceShip x y ori : x - first coord , y - second coord , ori - Orientation(v/h)\n Fire x y: x - first coord , y - second coord \n Save : without args\n Load : without args\n UseAbility : without args\n"<< '\n';
}