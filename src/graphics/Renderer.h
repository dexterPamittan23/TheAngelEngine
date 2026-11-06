#pragma once
#include <SDL.h>

// Logical resolution matches the Nintendo DS single-screen size (256x192).
constexpr int LOGICAL_W = 256;
constexpr int LOGICAL_H = 192;

class Renderer {
public:
    Renderer() = default;
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool init(const char* title, int scale);
    void beginFrame(Uint8 r, Uint8 g, Uint8 b);
    void endFrame();

    void fillRect(int x, int y, int w, int h, SDL_Color c);
    void drawRect(int x, int y, int w, int h, SDL_Color c);

    SDL_Renderer* sdl() const { return renderer_; }

private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};
