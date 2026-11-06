#include "core/Input.h"
#include <cstring>

void Input::beginFrame() { std::memcpy(prev_, keys_, sizeof(keys_)); }

void Input::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && !e.key.repeat) keys_[e.key.keysym.scancode] = true;
    else if (e.type == SDL_KEYUP) keys_[e.key.keysym.scancode] = false;
}

bool Input::up() const    { return held(SDL_SCANCODE_W) || held(SDL_SCANCODE_UP); }
bool Input::down() const  { return held(SDL_SCANCODE_S) || held(SDL_SCANCODE_DOWN); }
bool Input::left() const  { return held(SDL_SCANCODE_A) || held(SDL_SCANCODE_LEFT); }
bool Input::right() const { return held(SDL_SCANCODE_D) || held(SDL_SCANCODE_RIGHT); }
bool Input::interactPressed() const { return pressed(SDL_SCANCODE_Z) || pressed(SDL_SCANCODE_RETURN); }
bool Input::cancelPressed() const   { return pressed(SDL_SCANCODE_X) || pressed(SDL_SCANCODE_ESCAPE); }
bool Input::run() const { return held(SDL_SCANCODE_LSHIFT) || held(SDL_SCANCODE_RSHIFT); }
