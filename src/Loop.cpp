#include <Loop.h>


void Loop::run(Window& window, Renderer& renderer, Transformer& transformer) {
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
        renderer.Render(transformer);

        SDL_GL_SwapWindow(window.getSDLWindow());
    }
}
