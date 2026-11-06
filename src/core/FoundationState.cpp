#include "core/FoundationState.h"
#include "core/Game.h"

FoundationState::FoundationState(Game& game) : GameState(game) {
    camera_.setWorldSize(MAP_W * TILE, MAP_H * TILE);
}

void FoundationState::update(double dt) {
    Input& in = game_.input();
    if (in.cancelPressed()) { game_.quit(); return; }

    double dx = (in.right() ? 1 : 0) - (in.left() ? 1 : 0);
    double dy = (in.down() ? 1 : 0) - (in.up() ? 1 : 0);
    if (dx != 0 && dy != 0) { dx *= 0.7071; dy *= 0.7071; }

    double speed = in.run() ? 96.0 : 56.0;  // pixels/second
    constexpr double SIZE = 12;
    px_ += dx * speed * dt;
    py_ += dy * speed * dt;
    if (px_ < 0) px_ = 0;
    if (py_ < 0) py_ = 0;
    if (px_ > MAP_W * TILE - SIZE) px_ = MAP_W * TILE - SIZE;
    if (py_ > MAP_H * TILE - SIZE) py_ = MAP_H * TILE - SIZE;

    camera_.follow(px_ + SIZE / 2, py_ + SIZE / 2);
}

void FoundationState::render() {
    Renderer& r = game_.renderer();
    r.beginFrame(20, 20, 28);

    const SDL_Color grassA{96, 160, 88, 255}, grassB{88, 148, 80, 255};
    int cx = camera_.x(), cy = camera_.y();
    int x0 = cx / TILE, y0 = cy / TILE;
    for (int ty = y0; ty <= y0 + LOGICAL_H / TILE + 1 && ty < MAP_H; ++ty)
        for (int tx = x0; tx <= x0 + LOGICAL_W / TILE + 1 && tx < MAP_W; ++tx)
            r.fillRect(tx * TILE - cx, ty * TILE - cy, TILE, TILE, ((tx + ty) & 1) ? grassA : grassB);

    r.drawRect(-cx, -cy, MAP_W * TILE, MAP_H * TILE, {255, 255, 255, 255});

    int sx = static_cast<int>(px_) - cx, sy = static_cast<int>(py_) - cy;
    r.fillRect(sx, sy, 12, 12, {200, 190, 170, 255});
    r.drawRect(sx, sy, 12, 12, {40, 30, 30, 255});

    r.endFrame();
}
