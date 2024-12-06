#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> 
#include "AbilityManager.hpp"
#include "Manager.hpp"
#include "Game.hpp"
#include "GameState.hpp"

int main() {
    Manager userManager = Manager({4,3,1}, 3);

    GameState gameState;

    userManager[0].SetOri(Ship::Orientation::Hori);
    userManager[1].SetOri(Ship::Orientation::Vert);
    userManager[2].SetOri(Ship::Orientation::Vert);

    GameMap userField(10);
    try{
        userField.TakeShip({2, 2},&userManager[0], 0);
        gameState.addUserCoord(2,2);
    }catch(const std::exception& e){
        std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
    }
    try{
        userField.TakeShip({4, 6},&userManager[1],  1);
        gameState.addUserCoord(4,6);
    }catch(const std::exception& e){
       std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
    }
    try{
        userField.TakeShip({9, 9},&userManager[2], 2);
        gameState.addUserCoord(9,9);
    }catch(const std::exception& e){
        std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
    }
    gameState.setUserManager(&userManager);
    gameState.setUserField(&userField);


    Game game = Game(&gameState);
    game.createEnemiesItems();
    game.userTurn();
    game.enemyTurn();
    game.userTurn();
    game.enemyTurn();
    game.userTurn();
    game.enemyTurn();

    game.load();
    std::cout<<"----------------loading------------------" <<'\n';
    std::cout<<"-----------------------------"<<'\n';
    game.playRound();
    return 0;
}
