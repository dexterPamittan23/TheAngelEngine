#pragma once
#include "core/GameState.h"
#include "core/Input.h"
#include "graphics/Renderer.h"
#include <memory>
#include <vector>

class Game {
public:
    Game() = default;
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    bool init();
    void run();
    void quit() { running_ = false; }

    // State stack: the top state is updated/rendered.
    void pushState(std::unique_ptr<GameState> s);
    void popState();

    Renderer& renderer() { return renderer_; }
    Input& input() { return input_; }
    bool audioAvailable() const { return audioOk_; }

private:
    Renderer renderer_;
    Input input_;
    std::vector<std::unique_ptr<GameState>> states_;
    bool running_ = false;
    bool audioOk_ = false;
    bool sdlUp_ = false;
};
