#include "GameDisplay.hpp"
template <typename Renderer>
GameDisplay::GameDisplay(Renderer rendererInstance) : renderer(rendererInstance) {}

void GameDisplay::render(const GameState& state){
    render.renderState(state);
}
