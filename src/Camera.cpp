#include "Camera.h"


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

void Camera::MouseControl(float xChange, float yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch -= yChange;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    update();
}

glm::vec3 Camera::getCameraPosition() {
    return cameraPos;
}

glm::vec3 Camera::getCameraDirection() {
    return glm::normalize(cameraFront);
}

void Camera::update() {
    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

    void Camera::MoveCameraForwards(float deltaTime) {
        cameraPos += cameraFront * (movementSpeed * deltaTime);
    }
    void Camera::MoveCameraBackwards(float deltaTime) {
        cameraPos -= cameraFront * (movementSpeed * deltaTime);
    }
    void Camera::MoveCameraLeft(float deltaTime) {
        cameraPos -= cameraRight * (movementSpeed * deltaTime);
    }
    void Camera::MoveCameraRight(float deltaTime) {
        cameraPos += cameraRight * (movementSpeed * deltaTime);
    }

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
