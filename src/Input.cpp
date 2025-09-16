#include "Input.h"
#include <iostream>


Input::Input() {

}

Input::~Input() {

}

/**
void Input::HandleKeys(Window& window, SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        e.key.keysym.sym = true;
        printf("Key down: %s\n", SDL_GetKeyName(e.key.keysym.sym));
    }
    else if (e.type == SDL_KEYUP) {
        e.key.keysym.sym = false;
        printf("Key up: %s\n", SDL_GetKeyName(e.key.keysym.sym));
    }

    switch( e.type ) {
        case SDL_KEYDOWN:
            switch( e.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    SDL_Quit();
                case SDLK_LEFT:
                    printf("left");
                    break;
                case SDLK_RIGHT:
                    printf("right");
                    break;
                case SDLK_UP:
                    printf("up");
                    break;
                case SDLK_DOWN:
                    printf("down");
                    break;
                case SDLK_w:
                    break;
                case SDLK_s:
                    break;
                case SDLK_a:
                    break;
                case SDLK_d:
                    break;
                default:
                    break;
            }
    }
}

void Input::KeyDown(Window& window, SDL_Keycode key) {

}
*/

void Input::HandleMouse(Window& window, SDL_Event& e) {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if (e.type == SDL_MOUSEMOTION) {
        std::cout << "Mouse Motion Detected - "
                  << "x: " << e.motion.x
                  << ", y: " << e.motion.y << '\n';
    }
}
