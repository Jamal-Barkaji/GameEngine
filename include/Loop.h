#pragma once

#include "Window.h"
#include "Renderer.h"


class Loop {
public:
    void run(Window& window, Renderer& renderer, Transformer& transformer);
};

