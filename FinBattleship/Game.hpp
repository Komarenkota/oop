#ifndef GAME_H
#define GAME_H
#include "GameMap.hpp"
#include "Manager.hpp"
#include "AbilityManager.hpp"
#include "GameState.hpp"
#include <iostream>
#include <vector>


class Game {
public:
    Game(GameState* gameState);

    void reloadGame();              
    void userTurn(int x, int y, bool useAbil);              
    void enemyTurn();             
    bool isRoundOver() const;  
    void collocationEnemyShips();
    void save();
    void load();
    void createEnemiesItems();
    void createNewShipsManager();
    int getPhase();
    void putShip(int x, int y, Ship::Orientation ori);
    GameState* getState();
    void setAbilManager();
    void rePutsOfUserEnt();
private:
    GameState* gameState;
};

#endif