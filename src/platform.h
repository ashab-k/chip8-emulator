#ifndef  PLATFORM_H
#define PLATFORM_H
#include <SDL.h>
#include <cstdint>

class Platform
{
public:
    Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
    {
        // Initialize member variables
        window = nullptr;
        renderer = nullptr;
        texture = nullptr;
        
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("SDL_Init Error: %s", SDL_GetError());
            return;
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
        if (!window) {
            SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
            return;
        }

        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            textureWidth,
            textureHeight
        );
        if (!texture) {
            SDL_Log("SDL_CreateTexture Error: %s", SDL_GetError());
            return;
        }
    }

    ~Platform()
    {
        if (texture) SDL_DestroyTexture(texture);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Update(void const* buffer, int pitch)
    {
        SDL_UpdateTexture(texture, nullptr, buffer, pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    bool ProcessInput(uint8_t* keys)
    {
        bool quit = false;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                HandleKey(event.key.keysym.sym, keys, 1, quit);
                break;

            case SDL_KEYUP:
                HandleKey(event.key.keysym.sym, keys, 0, quit);
                break;
            }
        }

        return quit;
    }

private:
    void HandleKey(SDL_Keycode key, uint8_t* keys, uint8_t value, bool& quit)
    {
        switch (key) {
        case SDLK_ESCAPE: quit = true; break;
        case SDLK_x: keys[0] = value; break;
        case SDLK_1: keys[1] = value; break;
        case SDLK_2: keys[2] = value; break;
        case SDLK_3: keys[3] = value; break;
        case SDLK_q: keys[4] = value; break;
        case SDLK_w: keys[5] = value; break;
        case SDLK_e: keys[6] = value; break;
        case SDLK_a: keys[7] = value; break;
        case SDLK_s: keys[8] = value; break;
        case SDLK_d: keys[9] = value; break;
        case SDLK_z: keys[0xA] = value; break;
        case SDLK_c: keys[0xB] = value; break;
        case SDLK_4: keys[0xC] = value; break;
        case SDLK_r: keys[0xD] = value; break;
        case SDLK_f: keys[0xE] = value; break;
        case SDLK_v: keys[0xF] = value; break;
        }
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif