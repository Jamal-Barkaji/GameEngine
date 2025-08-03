#include "Window.h"
#include <iostream>


Window::Window() {
    init();
}

Window::~Window() {
    close();
}

bool Window::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( gWindow == nullptr ) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else {
            SDL_GLContext glContext = SDL_GL_CreateContext(gWindow);
        }
    }
    return success;
}


void Window::close() {
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Window* Window::getSDLWindow() const {
    return gWindow;
}
