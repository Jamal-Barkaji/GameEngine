#include "Loop.h"

#include "Input.h"


void Loop::run(Window& window, Renderer& renderer, Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList) {
        bool quit = false;
        SDL_Event e;

        while (!quit) {
                while (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                                quit = true;
                        }
                        switch( e.type ) {
                            case SDL_KEYDOWN:
                                switch( e.key.keysym.sym ) {
                                    case SDLK_ESCAPE:
                                        quit = true;
                                        break;
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
                                        camera.MoveCameraForwards();
                                        break;
                                    case SDLK_s:
                                        camera.MoveCameraBackwards();
                                        break;
                                    case SDLK_a:
                                        camera.MoveCameraLeft();
                                        break;
                                    case SDLK_d:
                                        camera.MoveCameraRight();
                                        break;
                                    default:
                                        break;
                                        // TODO: handle keyboard/mouse/etc.
                                }
                        }
                }
            Input::HandleMouse(window, e);

            camera.update();

            //Transforming
            transformer.transform();
            //Rendering
            renderer.RenderMesh(transformer, camera, shader, meshList);

            window.swapBuffers();
        }
}