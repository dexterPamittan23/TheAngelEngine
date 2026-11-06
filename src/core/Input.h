#pragma once
#include <SDL.h>

// Polled keyboard input with per-frame "pressed" edge detection.
class Input {
public:
    void beginFrame();                       // call once per frame before events
    void handleEvent(const SDL_Event& e);

    bool held(SDL_Scancode s) const { return keys_[s]; }
    bool pressed(SDL_Scancode s) const { return keys_[s] && !prev_[s]; }

    bool up() const;
    bool down() const;
    bool left() const;
    bool right() const;
    bool interactPressed() const;
    bool cancelPressed() const;
    bool run() const;

private:
    bool keys_[SDL_NUM_SCANCODES] = {};
    bool prev_[SDL_NUM_SCANCODES] = {};
};
