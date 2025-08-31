#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"


class Camera {
    public:
        Camera(Window& window);
        ~Camera();

        glm::mat4 getProjection() const;

    private:
        float fovy, aspect, zNear, zFar;
        glm::mat4 projection;
};
