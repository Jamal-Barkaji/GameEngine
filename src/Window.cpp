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
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        #ifdef __APPLE__
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        #endif


        //Create window
        gWindow = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );
        if( gWindow == nullptr ) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else {
            glContext = SDL_GL_CreateContext(gWindow);
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

int Window::getScreenWidth() {
    return screenWidth;
}

int Window::getScreenHeight() {
    return screenHeight;
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(gWindow);
}