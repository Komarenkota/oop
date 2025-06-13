#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> 
#include "AbilityManager.hpp"
#include "Manager.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "GameDisplay.hpp"
#include "ConsoleRenderer.hpp"
#include "GameController.hpp"
#include "CommandParser.hpp"

int main() {
    Manager userManager = Manager({4,3,1}, 3);

    GameState gameState;

    GameMap userField(10);

    gameState.setUserManager(&userManager);
    gameState.setUserField(&userField);
    ConsoleRenderer render;
    GameDisplay<ConsoleRenderer> display(render);
    Game game = Game(&gameState);

    
    std::cout<<game.getPhase()<<'\n';
    CommandParser parser;
    std::cout<<game.getPhase()<<'\n';
    GameController controller = GameController(game,parser, display);    
    std::cout<<game.getPhase()<<'\n';
    controller.processInput();
    std::cout<<game.getPhase()<<'\n';

    return 0;
}
