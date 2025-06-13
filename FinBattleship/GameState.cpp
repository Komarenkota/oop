#include "GameState.hpp"
#include "Exceptions.hpp"
#include <sstream>

GameState::GameState()
    {
}


std::string GameState::saveAll(){
    std::string data;

    size_t shipCount = this->getUserManager()->getShips().size();

    data = std::to_string(shipCount) + ' ';

    for (size_t i = 0; i < shipCount; ++i) {
        Ship& ship = (*this->getUserManager())[i];
        for (size_t x = 0; x < size_t(this->getUserField()->GetSide()); ++x) {
            for (size_t y = 0; y < size_t(this->getUserField()->GetSide()); ++y) {
                const Cell& cell = this->getUserField()->GetCell(x, y);          
                if (cell.checkSeg()) {
                    data += std::to_string(this->getUserCoord(i).first) +  ' ' + std::to_string(this->getUserCoord(i).second) + ' ';  
                    Ship::Orientation orientation = ship.GetOrientation();
                    if(orientation == Ship::Orientation::Hori){    
                        data += 'H' + ' ';
                    }else{
                        data += 'V' + ' ';
                    }
                    size_t segmentCount = ship.getSegments().size();
                    data += ' '+std::to_string(segmentCount) + ' ';
                    for (const Segment& segment : ship.getSegments()) {
                        auto condition = segment.GetCondition();
                        data += std::to_string(condition) + ' ';
                    }
                    goto next_ship;
                }
            }
        }
    next_ship:
        continue;
    }

    shipCount = this->getEnemyManager()->getShips().size();

    data += std::to_string(shipCount) + ' ';

    for (size_t i = 0; i < shipCount; ++i) {
        Ship& ship = (*this->getEnemyManager())[i];
        for (size_t x = 0; x < size_t(this->getEnemyField()->GetSide()); ++x) {
            for (size_t y = 0; y < size_t(this->getEnemyField()->GetSide()); ++y) {
                const Cell& cell = this->getEnemyField()->GetCell(x, y);        
                if (cell.checkSeg()) {
                    data += std::to_string(this->getEnemyCoord(i).first) +  ' ' + std::to_string(this->getEnemyCoord(i).second) + ' ';
                    Ship::Orientation orientation = ship.GetOrientation();
                    if(orientation == Ship::Orientation::Hori){    
                        data += 'H' + ' ';
                    }else{
                        data += 'V' + ' ';
                    }
                    size_t segmentCount = ship.getSegments().size();
                    data += ' '+std::to_string(segmentCount) + ' ';
                    for (const Segment& segment : ship.getSegments()) {
                        auto condition = segment.GetCondition();
                        data += std::to_string(condition) + ' ';
                    }
                    goto next_ship_en;
                }
            }
        }
    next_ship_en:
        continue;
    }
    for (size_t x = 0; x < size_t(this->getEnemyField()->GetSide()); ++x) {
            for (size_t y = 0; y < size_t(this->getEnemyField()->GetSide()); ++y) {
                if(this->getEnemyField()->GetCell(x, y).GetStatus() == Cell::Status::empty){
                    data += 'e';
                }else if(this->getEnemyField()->GetCell(x, y).GetStatus() == Cell::Status::ship_present){
                    data += 's' ; 
                }else{
                    data += 'u' ;
                }
                data += ' ';
            }
    }
    data += std::to_string(abilManager->getLenQueue());
    return data;
}


std::ostream& operator<< (std::ostream &os, GameState& gameState) {
    std::string resOfSave;
    resOfSave = gameState.saveAll();
    os << resOfSave << '\n';
    os << gameState.calculateChecksum(resOfSave);
    return os;
}

void GameState::loadAll(std::string data){
    std::istringstream in(data);// делаем из строки поток для удобного парса

    this->cleanUserCoord();
    int shipCount;
    int userCoords1;
    int userCoords2; 
    std::vector<std::string> orientations;
    std::vector<int> lens;
    std::vector<std::vector<int>> conditions;
    in >> shipCount ;
    for(int i = 0; i < shipCount; i++){
        std::vector<int> condition;
        std::string ori;
        int len;
        in >> userCoords1 >> userCoords2 >> ori >> len;
        orientations.push_back(ori);
        this->addUserCoord(userCoords1, userCoords2);
        lens.push_back(len);
        for(int j = 0; j < lens[i]; j++){
            int cond;
            in >> cond;
            condition.push_back(cond);
        }
        conditions.push_back(condition);
    }     
    Manager* userManager = new Manager(lens, shipCount);
    GameMap* userField = new GameMap(10);
    this->setUserManager(userManager);
    for(int i = 0; i < shipCount; i++){
        for(int j = 0; j < lens[i]; j++){
            (*userManager)[i].GetPtrSeg(j).setCondition(conditions[i][j]);
        }
        if(orientations[i] == "h"){
             (*userManager)[i].SetOri(Ship::Orientation::Hori);
        }else{
             (*userManager)[i].SetOri(Ship::Orientation::Vert);
        }
        userField->TakeShip({this->getUserCoord(i).first, this->getUserCoord(i).second}, &(*this->getUserManager())[i], i);
    } 
    this->setUserField(userField);

    this->cleanEnemyCoord();
    int enemyShipCount;
    int enemyCoords1;
    int enemyCoords2; 
    std::vector<std::string> enemyOrientations;
    std::vector<int> enemyLens;
    std::vector<std::vector<int>> enemyConditions;
    in >> enemyShipCount ;
    for(int i = 0; i < enemyShipCount; i++){
        std::vector<int> enemyCondition;
        std::string enemyOri;
        int enemyLen;
        in >> enemyCoords1 >> enemyCoords2 >> enemyOri >> enemyLen;
        enemyOrientations.push_back(enemyOri);
        this->addEnemyCoord(enemyCoords1, enemyCoords2);
        enemyLens.push_back(enemyLen);
        for(int j = 0; j < enemyLens[i]; j++){
            int enemyCond;
            in >> enemyCond;
            enemyCondition.push_back(enemyCond);
        }
        enemyConditions.push_back(enemyCondition);
    }

    Manager* enemyManager = new Manager(enemyLens, enemyShipCount);
    GameMap* enemyField = new GameMap(10);
    this->setEnemyManager(enemyManager);
    for(int i = 0; i < enemyShipCount; i++){
        for(int j = 0; j < enemyLens[i]; j++){
            (*enemyManager)[i].GetPtrSeg(j).setCondition(enemyConditions[i][j]);
        }
        if(enemyOrientations[i] == "h"){
             (*enemyManager)[i].SetOri(Ship::Orientation::Hori);
        }else{
             (*enemyManager)[i].SetOri(Ship::Orientation::Vert);
        }
        enemyField->TakeShip({this->getEnemyCoord(i).first, this->getEnemyCoord(i).second}, &(*this->getEnemyManager())[i], i);
    }
    for(int i = 0; i < 10; i++ ){
        for(int j = 0; j < 10; j++){
            std::string status;
            status.clear();
            in >> status;   
            if(status == "e"){    
                enemyField->GetCell(i,j).SetStatus(Cell::Status::empty);
            }else if(status == "s"){
                enemyField->GetCell(i,j).SetStatus(Cell::Status::ship_present);
            }else{
                enemyField->GetCell(i,j).SetStatus(Cell::Status::unknown);
            }
        }
    } 
    this->setEnemyField(enemyField);

    int sizeOfQueue;
    in >> sizeOfQueue;
    AbilityManager* abilManager = new AbilityManager();
    abilManager->setField(enemyField);
    for(int i = 0; i < sizeOfQueue; i++){
        abilManager->addRandomAbility();
    } 
    this->setAbilManager(abilManager);
}

std::istream& operator>> (std::istream &in, GameState& gameState){
    std::string data;
    std::getline(in, data);
    unsigned int holdCheckSum;
    in >> holdCheckSum;
    if(holdCheckSum != gameState.calculateChecksum(data)){ 
        throw incorrectCheckSum();
    }else{
        gameState.loadAll(data);
    } 
    return in;
}





void GameState::clearFile(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для очистки.");
    }
    outFile.close();
}

unsigned int GameState::calculateChecksum(const std::string& data) {
    const unsigned int base = 31; 
    const unsigned int mod = 1e9 + 7; 
    unsigned int hash = 0;
    unsigned int power = 1;

    for (char c : data) {
        hash = (hash + (static_cast<unsigned int>(c) * power) % mod) % mod;
        power = (power * base) % mod;
    }

    return hash;
}



void GameState::setUserField(GameMap* userField) {
    this->userField = userField;
}

GameMap* GameState::getUserField() {
    return userField;
}

void GameState::setEnemyField(GameMap* enemyField) {
    this->enemyField = enemyField;
}

GameMap* GameState::getEnemyField() {
    return enemyField;
}

void GameState::setUserManager(Manager* userManager) {
    this->userManager = userManager;
}

Manager* GameState::getUserManager() {
    return userManager;
}

void GameState::setEnemyManager(Manager* enemyManager) {
    this->enemyManager = enemyManager;
}

Manager* GameState::getEnemyManager() {
    return enemyManager;
}

void GameState::setAbilManager(AbilityManager* abilManager) {
    this->abilManager = abilManager;
}

AbilityManager* GameState::getAbilManager() {
    return abilManager;
}

void GameState::addUserCoord(int x, int y) {
    userShipsCoord.emplace_back(x, y); 
}

std::pair<int,int> GameState::getUserCoord(int idx){
    return this->userShipsCoord[idx];
}

void GameState::cleanUserCoord(){
    this->userShipsCoord.clear();
}

void GameState::addEnemyCoord(int x, int y) {
    enemyShipsCoord.emplace_back(x, y);
}

std::pair<int,int> GameState::getEnemyCoord(int idx){
    return this->enemyShipsCoord[idx];
}

void GameState::cleanEnemyCoord(){
    this->enemyShipsCoord.clear();
}

void GameState::setCountOfUnPlaceShips(int newCount){
    this->countOfUnPlaceShips = newCount;
}

int GameState::getCountOfUnPlaceShips(){
    return this->countOfUnPlaceShips;
}

int GameState::getPhase(){
    return this->phase;
}

void GameState::setPhase(int phase){
    this->phase = phase;
}