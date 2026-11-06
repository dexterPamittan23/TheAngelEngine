#pragma once
#include <SDL.h>

class Game;

// Base class for every screen/mode (title, overworld, dialogue, endings...).
class GameState {
public:
    explicit GameState(Game& game) : game_(game) {}
    virtual ~GameState() = default;

    virtual void onEnter() {}
    virtual void handleEvent(const SDL_Event& e) { (void)e; }
    virtual void update(double dt) = 0;
    virtual void render() = 0;

protected:
    Game& game_;
};
