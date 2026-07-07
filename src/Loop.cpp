#include "Loop.h"

#include "Input.h"
#include "PhysicsSystem.h"
#include "Scene.h"


void Loop::run(Window& window, IRenderer& renderer, Transformer& transformer, Camera& camera, Scene& scene, IShader& mainShader, IShader& directionalShadowShader, IShader& omniShadowShader, PhysicsSystem& physics) {
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
                        camera.mouseControl(e.motion.xrel, e.motion.yrel);
                    }
                }
                const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
                if (keyStates[SDL_SCANCODE_W]) {
                    camera.moveCameraForwards(deltaTime);
                }
                if (keyStates[SDL_SCANCODE_S]) {
                    camera.moveCameraBackwards(deltaTime);
                }
                if (keyStates[SDL_SCANCODE_A]) {
                    camera.moveCameraLeft(deltaTime);
                }
                if (keyStates[SDL_SCANCODE_D]) {
                    camera.moveCameraRight(deltaTime);
                }
            // TODO: Remember to compartmentalise input logic in Input class later

            physics.step(camera, scene.entities, deltaTime);

            // TODO: Consider moving this logic to a separate updateScene function in Loop or Scene class later
            if (!scene.spotLights.empty()) {
                glm::vec3 lowerLight = camera.getCameraPosition();
                lowerLight.y -= 0.3f;

                scene.spotLights[0].setFlash(lowerLight, camera.getCameraDirection());
            }

            //Transforming
            transformer.transform();
            //Rendering
            renderer.renderFrame(scene, camera, mainShader, directionalShadowShader, omniShadowShader);
        }
}