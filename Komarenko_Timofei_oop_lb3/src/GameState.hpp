#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include "GameMap.hpp"
#include "Manager.hpp"
#include "AbilityManager.hpp"
#include <vector>
#include <iostream>
#include <fstream>

class GameState {
private:
    Manager* userManager;
    Manager* enemyManager;
    GameMap* userField;
    GameMap* enemyField;
    AbilityManager* abilManager;

    std::vector<std::pair<int, int>> userShipsCoord;
    std::vector<std::pair<int, int>> enemyShipsCoord;
public:
    GameState();

    void loadAll(std::string data);

    std::string saveAll();

    friend std::ostream& operator<<(std::ostream &os, GameState& gameState);

    friend std::istream& operator>>(std::istream &in, GameState& gameState);

    void clearFile(const std::string& filename);

    unsigned int calculateChecksum(const std::string& data);

    void setUserField(GameMap* userField);

    GameMap* getUserField();

    void setEnemyField(GameMap* enemyField);

    GameMap* getEnemyField();

    void setUserManager(Manager* userManager);

    Manager* getUserManager();

    void setEnemyManager(Manager* enemyManager);

    Manager* getEnemyManager();

    void setAbilManager(AbilityManager* abilManager);

    AbilityManager* getAbilManager();

    void addUserCoord(int x, int y);

    std::pair<int,int> getUserCoord(int idx);

    void cleanUserCoord();

    void addEnemyCoord(int x, int y);

    std::pair<int,int> getEnemyCoord(int idx);

    void cleanEnemyCoord();
};

#endif