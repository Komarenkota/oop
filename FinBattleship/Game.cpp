#include "Game.hpp"
#include "GameState.hpp"
#include "Exceptions.hpp"
#include "FileWrapper.hpp"

Game::Game(GameState* gameState):gameState(gameState)
      {
        gameState->setPhase(0);
      }

void Game::collocationEnemyShips() {
    GameMap* enemyField = new GameMap(10);
    srand(static_cast<unsigned>(time(nullptr)));
    
    for (size_t i = 0; i < 3; i++) {
        Ship& ship = (*gameState->getEnemyManager())[i];
        Ship::Orientation orientation = (rand() % 2 == 0)
                                            ? Ship::Orientation::Hori
                                            : Ship::Orientation::Vert;
        ship.SetOri(orientation);
    }

    for (size_t i = 0; i < 3; i++) {
        bool placed = false;
        while (!placed) {
            int x = (rand() % enemyField->GetSide()+1);
            int y = (rand() % enemyField->GetSide()+1);    

            try {
                Ship& ship = (*gameState->getEnemyManager())[i];
                enemyField->TakeShip({x, y}, &ship, i); 
                gameState->addEnemyCoord(x, y);
                placed = true;
            } catch (const std::exception& e) {
                placed = false;
            }
        }
    }
    gameState->setEnemyField(enemyField);
    gameState->getEnemyField()->setCellsHidden();
    int countOfAbils;
    if(gameState->getAbilManager() != nullptr){
        countOfAbils = gameState->getAbilManager()->getLenQueue();
    }else{
        countOfAbils = 1;
    }
    if(countOfAbils < 0 || countOfAbils > 100){
        countOfAbils = 1;
    }
    gameState->setAbilManager(new AbilityManager);
    gameState->getAbilManager()->setField(gameState->getEnemyField());
    while(countOfAbils != 0){    
        gameState->getAbilManager()->addRandomAbility();
        countOfAbils -= 1;
    }
}

void Game::createNewShipsManager(){
    Manager* enemyShipsManager = new Manager({4, 3, 1}, 3);
    gameState->setEnemyManager(enemyShipsManager);

}

void Game::setAbilManager(){
    gameState->getAbilManager()->setField(gameState->getEnemyField());
}

void Game::createEnemiesItems(){
    createNewShipsManager();
    collocationEnemyShips();
}

void Game::reloadGame(){
    createEnemiesItems();
    gameState->setPhase(1);
}

void Game::rePutsOfUserEnt(){
    Manager* userShipsManager = new Manager({4, 3, 1}, 3);
    gameState->setUserManager(userShipsManager);
    GameMap* enemyField = new GameMap(10);
    gameState->setUserField(enemyField);
    reloadGame();
    gameState->setCountOfUnPlaceShips(3);
    gameState->setPhase(0);
}

void Game::userTurn(int x, int y, bool useAbil){
    if(useAbil){
        try{    
            gameState->getAbilManager()->useAbility();
        }catch(const std::exception& e){
            std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
        }
    }    
    if(gameState->getAbilManager()->isDoubleDamageActive()){
        try{
            gameState->getEnemyField()->DoubleDamageAttack(x,y);
            gameState->getAbilManager()->resetDoubleDamage();
        }catch(const std::exception& e){
            std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
        }
    }else{
        try{
            gameState->getEnemyField()->AttackCell(x, y);
        }catch(const std::exception& e){
            std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
        }
    }
    if(gameState->getEnemyManager()->checkNewSunk()){
        gameState->getAbilManager()->addRandomAbility();
    }
    if(isRoundOver()){
        reloadGame();
    }else{
        gameState->setPhase(2);
    }
}

void Game::enemyTurn(){
    size_t x = (rand() % (gameState->getUserField()->GetSide())+1);
    size_t y = (rand() % (gameState->getUserField()->GetSide())+1);
    std::cout << "Враг атакует ячейку (" << x << ", " << y << ")!\n";
    gameState->getUserField()->AttackCell(x, y);
    gameState->getUserManager()->checkNewSunk();

    if(isRoundOver()){
        gameState->setPhase(0);
        rePutsOfUserEnt();
    }else{
        gameState->setPhase(1);
    }
}


bool Game::isRoundOver() const {
    return (gameState->getUserManager()->checkAllSunk() || gameState->getEnemyManager()->checkAllSunk());
}

void Game::save(){
    std::string filename = "game.dat";
    FileWrapper fileWrapper = FileWrapper(filename, std::ios::out);
    fileWrapper.saveToFile(this->gameState);
}

void Game::load(){
    std::string filename = "game.dat";
    FileWrapper fileWrapper = FileWrapper(filename, std::ios::in);
    try{
        fileWrapper.loadFromFile(this->gameState);
    }catch(const std::exception& e){
        std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
    } 
    gameState->setPhase(1);
}


int Game::getPhase(){
    return gameState->getPhase();
}


void Game::putShip(int x, int y, Ship::Orientation ori){
    std::cout<< gameState->getCountOfUnPlaceShips()<< '\n';
    bool placed = false;
    int count;
    if(gameState->getCountOfUnPlaceShips() == 3){
        count = 0; 
    }else if(gameState->getCountOfUnPlaceShips() == 2){
        count = 1; 
    }else if(gameState->getCountOfUnPlaceShips() == 1){
        count = 2; 
    }
    (*gameState->getUserManager())[count].SetOri(ori);
    try{
        Ship& ship = (*gameState->getUserManager())[count];
        gameState->getUserField()->TakeShip({x, y}, &ship , count);
        gameState->addUserCoord(x,y);
        placed = true;
    }catch(const std::exception& e){
        std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
        placed = false;
    }
    if(placed == true){
        gameState->setCountOfUnPlaceShips(gameState->getCountOfUnPlaceShips() - 1);
    }
    if(gameState->getCountOfUnPlaceShips() == 0){
        gameState->setPhase(1);
    }
}


GameState* Game::getState(){
    return this->gameState;
}