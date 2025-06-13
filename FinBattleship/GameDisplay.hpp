#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "Game.hpp"
#include "ConsoleRenderer.hpp"
#include "GameState.hpp"

template <typename Renderer>
class GameDisplay {
private:
    Renderer renderer;
    
public:
    GameDisplay(Renderer rendererInstance);

    void render(GameState& state);

    void unknownCommand();

    void unknownOri();

    void clearDisplay();

    void inCorrectPhase();

    void inCorrectArgs();
};

template <typename Renderer>
GameDisplay<Renderer>::GameDisplay(Renderer rendererInstance) 
    : renderer(rendererInstance) {}

template <typename Renderer>
void GameDisplay<Renderer>::render(GameState& state) {
    renderer.renderState(state);
}

template <typename Renderer>
void GameDisplay<Renderer>::clearDisplay() {
    renderer.clearConsole();
}

template <typename Renderer>
void GameDisplay<Renderer>::unknownCommand() {
    renderer.unknownCommand();
}

template <typename Renderer>
void GameDisplay<Renderer>::unknownOri() {
    renderer.unknownOri();
}

template <typename Renderer>
void GameDisplay<Renderer>::inCorrectPhase() {
    renderer.inCorrectPhase();
}

template <typename Renderer>
void GameDisplay<Renderer>::inCorrectArgs(){
    renderer.inCorrectArgs();
}



#endif