#pragma once

#include <SDL.h>
#include <glad/glad.h>


class Window {
public:
    Window();
    ~Window();

    bool init();
    void close();

    SDL_Window* getSDLWindow() const;

    // TODO: RESIZE WINDOW LOGIC
    // void resize(screen_width, screen_height);

private:
    GLint SCREEN_WIDTH = 640;
    GLint SCREEN_HEIGHT = 480;

    SDL_Window* gWindow = nullptr;
};
