#include "Game.hpp"
#include "GameState.hpp"
#include "Exceptions.hpp"

Game::Game(GameState* gameState):gameState(gameState)
      {
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
    std::cout << "Поле врага:\n";
    gameState->getEnemyField()->PrintStat();
    std::cout << "------------------------------------\n";
    gameState->getEnemyField()->setCellsHidden();
    gameState->setAbilManager(new AbilityManager);
    gameState->getAbilManager()->setField(gameState->getEnemyField());
    gameState->getAbilManager()->addRandomAbility();
}

void Game::createNewShipsManager(){
    Manager* enemyShipsManager = new Manager({4, 3, 1}, 3);
    gameState->setEnemyManager(enemyShipsManager);

}

void Game::createEnemiesItems(){
    createNewShipsManager();
    collocationEnemyShips();
}

void Game::startNewGame(){
    createEnemiesItems();
    playRound();
}

void Game::playRound(){
    bool enemyLoss = false;
    bool userLoss = false;
    while(!(enemyLoss && userLoss)){
        
        std::cout<<"Ваше поле:"<<'\n';
        gameState->getUserField()->PrintStat();
        std::cout<<"Поле Врага:"<<'\n';
        gameState->getEnemyField()->PrintStat();

        userTurn();
        if(isRoundOver()){
            enemyLoss = true;
            std::cout << "Вы победили!"<< '\n';\
            startNewGame();
            break;
        }
        enemyTurn();
        if(isRoundOver()){
            userLoss = true;
            std::cout << "Вы проиграли!"<< '\n';
            break;
        }
    }
}

void Game::userTurn(){
    std::cout<<"Ваше поле:"<<'\n';
    gameState->getUserField()->PrintStat();
    std::cout<<"Поле Врага:"<<'\n';
    gameState->getEnemyField()->PrintStat();
    std::cout << "Ваш ход.\n";
    std::cout << "Вы хотите сохранится? ------[y / n]\n";
    std::string ans;
    std::cin >> ans;
    if(ans =="y"){
        save();
    }     
    try{    
        gameState->getAbilManager()->useAbility();
    }catch(const std::exception& e){
        std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
    }
    size_t x, y;
    std::cout << "Введите координаты для атаки (x y): ";
    std::cin >> x >> y;
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
        std::cout << "Вы победили!"<< '\n';\
        startNewGame();
    }
}

void Game::enemyTurn(){
    std::cout << "Ход врага.\n";
    size_t x = (rand() % (gameState->getUserField()->GetSide())+1);
    size_t y = (rand() % (gameState->getUserField()->GetSide())+1);
    std::cout << "Враг атакует ячейку (" << x << ", " << y << ")!\n";
    gameState->getUserField()->AttackCell(x, y);
    if(isRoundOver()){
        std::cout << "Вы проиграли!"<< '\n';
    }

}


bool Game::isRoundOver() const {
    return (gameState->getUserManager()->checkAllSunk() || gameState->getEnemyManager()->checkAllSunk());
}

void Game::save(){
    std::string filename = "game.dat";
    std::ofstream saveFile(filename);
    if(saveFile.is_open()){
        saveFile << (*this->gameState) << std::endl;
   }
    saveFile.close();
}

void Game::load(){
    std::string filename = "game.dat";
    std::ifstream in(filename);
    if(in.is_open()){
        try{
            in >> (*this->gameState);
        }catch(const std::exception& e){
            std::cerr << "Произошла ошибка!" << std::endl << e.what() << std::endl;
        } 
    }
    in.close();
}