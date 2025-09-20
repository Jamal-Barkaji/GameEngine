#include "Loop.h"

#include "Input.h"


void Loop::run(Window& window, Renderer& renderer, Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList) {
        bool quit = false;
        SDL_Event e;

        SDL_SetRelativeMouseMode(SDL_TRUE);

        while (!quit) {
            GLfloat currentTime = SDL_GetPerformanceCounter();
            deltaTime = (currentTime - lastTime) / (GLfloat)SDL_GetPerformanceFrequency();
            lastTime = currentTime;

                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    if ( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }

                    if (e.type == SDL_MOUSEMOTION) {
                        camera.MouseControl(e.motion.xrel, e.motion.yrel);
                    }
                }
                const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
                if (keyStates[SDL_SCANCODE_W]) {
                    camera.MoveCameraForwards(deltaTime);
                }
                if (keyStates[SDL_SCANCODE_S]) {
                    camera.MoveCameraBackwards(deltaTime);
                }
                if (keyStates[SDL_SCANCODE_A]) {
                    camera.MoveCameraLeft(deltaTime);
                }
                if (keyStates[SDL_SCANCODE_D]) {
                    camera.MoveCameraRight(deltaTime);
                }
            // TODO: Remember to compartmentalise input logic in Input class later


            //Transforming
            transformer.transform();
            //Rendering
            renderer.RenderMesh(transformer, camera, shader, meshList);

            window.swapBuffers();
        }
}