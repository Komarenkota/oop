#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "Game.hpp"
#include "CommandParser.hpp"
#include "GameDisplay.hpp"

template <typename CommandHandler,typename Renderer>
class GameController {
private:
    Game& game;                
    CommandHandler handler;
    GameDisplay<Renderer> display;
    bool flagOfUseAbil = false;
    bool isRunning = true;
public:
    GameController(Game& gameInstance, CommandHandler cmdHandler, GameDisplay<Renderer> display);

    void executeCommand(Command& command);

    void processInput();
};

template <typename CommandHandler,typename Renderer>
GameController<CommandHandler, Renderer>::GameController(Game& gameInstance, CommandHandler cmdHandler,GameDisplay<Renderer> display)
        : game(gameInstance), handler(cmdHandler), display(display) {
            game.createEnemiesItems();
        }


template <typename CommandHandler,typename Renderer>
void GameController<CommandHandler, Renderer>::executeCommand(Command& command){
    switch (command.type) {
            case CommandType::Fire:
                if (command.arguments.size() == 2) {
                    int x = std::stoi(command.arguments[0]);
                    int y = std::stoi(command.arguments[1]);
                    display.clearDisplay();
                    game.userTurn(x,y,this->flagOfUseAbil);
                    if(game.getState()->getPhase() == 2){    
                        game.enemyTurn();
                    }
                    display.render(*game.getState());
                    this->flagOfUseAbil = 0;
                }else{
                    display.clearDisplay();
                    display.inCorrectArgs();
                    display.render(*game.getState());
                }
                break;

            case CommandType::Load:
                if(command.arguments.size() == 0){
                    game.load();
                    display.clearDisplay();
                    display.render(*game.getState());
                }else{
                    display.clearDisplay();
                    display.inCorrectArgs();
                    display.render(*game.getState());
                }
                break;

            case CommandType::Save:
                if(command.arguments.size() == 0){
                    game.save();
                    display.clearDisplay();
                    display.render(*game.getState());
                }else{
                    display.clearDisplay();
                    display.inCorrectArgs();
                    display.render(*game.getState());
                }
                break;

            case CommandType::UseAbility:
                if(command.arguments.size() == 0){
                    this->flagOfUseAbil = true;
                    display.clearDisplay();
                    display.render(*game.getState());
                }else{
                    display.clearDisplay();
                    display.inCorrectArgs();
                    display.render(*game.getState());
                }
                break;

            case CommandType::PutShip:
                if(command.arguments.size() == 3){
                    int x = std::stoi(command.arguments[0]);
                    int y = std::stoi(command.arguments[1]);
                
                    if(command.arguments[2] == "h"){
                        Ship::Orientation ori = Ship::Orientation::Hori;
                        game.putShip(x,y,ori);
                    }else if(command.arguments[2] == "v"){
                        Ship::Orientation ori = Ship::Orientation::Vert;
                        game.putShip(x,y,ori);
                    }else{
                        display.clearDisplay();
                        display.unknownOri();
                        display.render(*game.getState());
                        break;
                    }
                    display.clearDisplay();
                    display.render(*game.getState());
                }else{
                    display.clearDisplay();
                    display.inCorrectArgs();
                    display.render(*game.getState());
                }
                break;
            case CommandType::Exit:
                display.clearDisplay();
                exit(0);
                isRunning = false;
                break;
            default:
                display.clearDisplay();
                display.unknownCommand();
                display.render(*game.getState());
    }
}



template <typename CommandHandler,typename Renderer>
void GameController<CommandHandler, Renderer>::processInput() {
    display.clearDisplay();
    display.render(*game.getState());   
    while((game.getPhase() == 0 || game.getPhase() == 1) && isRunning == true){
        while(game.getPhase() == 1){
                Command command = handler.parse(handler.waitCommand());
                if(command.type != CommandType::PutShip){
                    executeCommand(command);
                }else{
                    display.clearDisplay();
                    display.inCorrectPhase();
                    display.render(*game.getState());
                }
        }
        while(game.getPhase() == 0){
            Command command = handler.parse(handler.waitCommand());
            if(command.type == CommandType::PutShip || command.type == CommandType::Load || command.type == CommandType::Exit){
                executeCommand(command);
            }else{
                display.clearDisplay();
                display.inCorrectPhase();
                display.render(*game.getState());
            }
        }
    }
} 
#endif