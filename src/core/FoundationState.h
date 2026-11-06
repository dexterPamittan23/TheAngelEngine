#pragma once
#include "core/GameState.h"
#include "graphics/Camera.h"

// Milestone 1 test scene: a scrolling checkered world, a controllable square,
// and a following camera. Replaced by the real overworld in Milestone 2.
class FoundationState : public GameState {
public:
    explicit FoundationState(Game& game);
    void update(double dt) override;
    void render() override;

private:
    static constexpr int TILE = 16;
    static constexpr int MAP_W = 40;
    static constexpr int MAP_H = 30;

    double px_ = 20 * TILE, py_ = 15 * TILE;
    Camera camera_;
};
