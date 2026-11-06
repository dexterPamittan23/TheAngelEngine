#pragma once
#include "graphics/Renderer.h"
#include <algorithm>

class Camera {
public:
    void setWorldSize(int w, int h) { worldW_ = w; worldH_ = h; }

    // Centre on a target, clamped so the view never leaves the world.
    void follow(double cx, double cy) {
        x_ = std::clamp(cx - LOGICAL_W / 2.0, 0.0, static_cast<double>(std::max(0, worldW_ - LOGICAL_W)));
        y_ = std::clamp(cy - LOGICAL_H / 2.0, 0.0, static_cast<double>(std::max(0, worldH_ - LOGICAL_H)));
    }

    int x() const { return static_cast<int>(x_); }
    int y() const { return static_cast<int>(y_); }

private:
    double x_ = 0, y_ = 0;
    int worldW_ = LOGICAL_W, worldH_ = LOGICAL_H;
};
