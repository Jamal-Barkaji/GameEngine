#include "Window.h"
#include <iostream>


Window::Window() {}

Window::~Window() {
    close();
}

bool Window::init(uint32_t apiFlags) {
    bool success = true;

    gWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               screenWidth, screenHeight,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | apiFlags);

    if( gWindow == nullptr ) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        success = false;
    }

    return success;
}

void Window::close() {
    if (gWindow) {
        SDL_DestroyWindow( gWindow );
        gWindow = nullptr;
    }
    SDL_Quit();
}

SDL_Window* Window::getSDLWindow() const {
    return gWindow;
}

int Window::getScreenWidth() {
    return screenWidth;
}

int Window::getScreenHeight() {
    return screenHeight;
}