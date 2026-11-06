#include "graphics/Renderer.h"
#include <cstdio>

Renderer::~Renderer() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
}

bool Renderer::init(const char* title, int scale) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               LOGICAL_W * scale, LOGICAL_H * scale, SDL_WINDOW_RESIZABLE);
    if (!window_) { std::fprintf(stderr, "Window: %s\n", SDL_GetError()); return false; }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer_) { std::fprintf(stderr, "Renderer: %s\n", SDL_GetError()); return false; }

    SDL_RenderSetLogicalSize(renderer_, LOGICAL_W, LOGICAL_H);
    SDL_RenderSetIntegerScale(renderer_, SDL_TRUE);  // crisp pixels
    return true;
}

void Renderer::beginFrame(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
    SDL_RenderClear(renderer_);
}

void Renderer::endFrame() { SDL_RenderPresent(renderer_); }

void Renderer::fillRect(int x, int y, int w, int h, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
    SDL_Rect r{x, y, w, h};
    SDL_RenderFillRect(renderer_, &r);
}

void Renderer::drawRect(int x, int y, int w, int h, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
    SDL_Rect r{x, y, w, h};
    SDL_RenderDrawRect(renderer_, &r);
}
