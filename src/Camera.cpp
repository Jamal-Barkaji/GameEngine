#include "Camera.h"


Camera::Camera(Window& window) {
    fovy = 45.0;
    aspect = static_cast<float>(window.getScreenWidth())/static_cast<float>(window.getScreenHeight());
    zNear = 0.1f;
    zFar = 100.0f;
    projection = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

Camera::~Camera() {}

glm::mat4 Camera::getProjection() const {
    return projection;
}
