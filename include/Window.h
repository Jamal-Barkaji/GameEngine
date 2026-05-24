#pragma once

#include <SDL.h>


class Window {
public:
    Window();
    ~Window();

    bool init(uint32_t apiFlags);
    void close();

    SDL_Window* getSDLWindow() const;
    int getScreenWidth();
    int getScreenHeight();


private:
    int screenWidth = 1366;
    int screenHeight = 768;

    SDL_Window* gWindow = nullptr;
};