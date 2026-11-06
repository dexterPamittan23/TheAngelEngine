#include "core/Game.h"
#include "core/FoundationState.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdio>

Game::~Game() {
    states_.clear();
    if (audioOk_) Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    if (sdlUp_) SDL_Quit();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        // Retry without audio so headless/no-audio machines still work.
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            std::fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
            return false;
        }
    }
    sdlUp_ = true;

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
        std::fprintf(stderr, "IMG_Init warning: %s\n", IMG_GetError());
    if (TTF_Init() != 0)
        std::fprintf(stderr, "TTF_Init warning: %s\n", TTF_GetError());
    audioOk_ = (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 0);
    if (!audioOk_) std::fprintf(stderr, "Audio disabled: %s\n", Mix_GetError());

    if (!renderer_.init("THE ANGEL ENGINE", 4)) return false;

    pushState(std::make_unique<FoundationState>(*this));
    running_ = true;
    return true;
}

void Game::pushState(std::unique_ptr<GameState> s) {
    states_.push_back(std::move(s));
    states_.back()->onEnter();
}

void Game::popState() {
    if (!states_.empty()) states_.pop_back();
    if (states_.empty()) running_ = false;
}

void Game::run() {
    Uint64 last = SDL_GetPerformanceCounter();
    const double freq = static_cast<double>(SDL_GetPerformanceFrequency());

    while (running_ && !states_.empty()) {
        Uint64 now = SDL_GetPerformanceCounter();
        double dt = static_cast<double>(now - last) / freq;
        last = now;
        if (dt > 0.1) dt = 0.1;  // avoid huge steps after window drags

        input_.beginFrame();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running_ = false; break; }
            input_.handleEvent(e);
            if (!states_.empty()) states_.back()->handleEvent(e);
        }
        if (!running_ || states_.empty()) break;

        states_.back()->update(dt);
        if (!running_ || states_.empty()) break;
        states_.back()->render();
    }
}
