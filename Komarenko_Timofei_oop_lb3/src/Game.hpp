#ifndef GAME_H
#define GAME_H
#include "GameMap.hpp"
#include "Manager.hpp"
#include "AbilityManager.hpp"
#include "GameState.hpp"
#include <iostream>
#include <vector>

//class AbilityManager;

class Game {
public:
    Game(GameState* gameState);

    void startNewGame();          
    void playRound();             
    void userTurn();              
    void enemyTurn();             
    bool isRoundOver() const;  
    void collocationEnemyShips();
    void save();
    void load();
    void createEnemiesItems();
    void createNewShipsManager();
private:
    GameState* gameState;
};

#endif