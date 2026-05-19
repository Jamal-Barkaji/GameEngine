#pragma once

#include <SDL.h>


class Window {
public:
    Window();
    ~Window();

    bool init();
    void close();

    SDL_Window* getSDLWindow() const;
    int getScreenWidth();
    int getScreenHeight();

    void swapBuffers();

    // TODO: RESIZE WINDOW LOGIC
    // void resize(screen_width, screen_height);

private:
    int screenWidth = 1366;
    int screenHeight = 768;

    SDL_Window* gWindow = nullptr;
    SDL_GLContext glContext;
};
