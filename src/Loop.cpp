#include "Loop.h"


void Loop::run(Window& window, Renderer& renderer, Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList) {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // TODO: handle keyboard/mouse/etc.
        }

        //Transforming
        transformer.transform();
        //Rendering
        renderer.RenderMesh(transformer, camera, shader, meshList);

        window.swapBuffers();
    }
}
