#ifndef CONSOLERENDERER_H
#define CONSOLERENDERER_H
#include "GameState.hpp"
#include <iostream>

class ConsoleRenderer {
public:
    void renderState(GameState& state);
    
    void clearConsole(); 

    void unknownCommand(); 

    void unknownOri();

    void inCorrectPhase();

    void inCorrectArgs();
};

#endif