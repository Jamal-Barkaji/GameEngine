#include <Window.h>
#include <Renderer.h>
#include <Loop.h>


int main(int argc, char* argv[]) {
        Window window;
        Renderer renderer;
        Transformer transformer;
        Loop loop;
        loop.run(window, renderer, transformer);
    return 0;
}
