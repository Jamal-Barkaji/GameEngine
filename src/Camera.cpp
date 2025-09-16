#include "Camera.h"
#include <iostream>

Camera::Camera(Window& window, glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed) {
    fovy = 45.0;
    aspect = static_cast<float>(window.getScreenWidth())/static_cast<float>(window.getScreenHeight());
    zNear = 0.1f;
    zFar = 100.0f;
    projection = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);

    cameraPos = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    movementSpeed = startMoveSpeed;
    turnSpeed = startTurnSpeed;

    update();
}

Camera::~Camera() {}

glm::mat4 Camera::getProjection() const {
    return projection;
}

void Camera::update() {
    std::cout << "Camera pos: "
          << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z
          << " looking at: "
          << (cameraPos + cameraFront).x << ", "
          << (cameraPos + cameraFront).y << ", "
          << (cameraPos + cameraFront).z << std::endl;


    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

    void Camera::MoveCameraForwards() {
        cameraPos += cameraFront * movementSpeed;
    }
    void Camera::MoveCameraBackwards() {
        cameraPos -= cameraFront * movementSpeed;
    }
    void Camera::MoveCameraLeft() {
        cameraPos -= cameraRight * movementSpeed;
    }
    void Camera::MoveCameraRight() {
        cameraPos += cameraRight * movementSpeed;
    }

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
