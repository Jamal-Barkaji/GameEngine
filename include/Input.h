#pragma once

#include <SDL.h>
#include "Window.h"


class Input {
    public:
        Input();
        ~Input();

        static void HandleKeys(Window& window, SDL_Event& e);
        static void KeyDown(Window& window, SDL_Keycode key);

        static void HandleMouse(Window& window, SDL_Event& e);

    private:

};
