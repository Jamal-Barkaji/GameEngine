#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"


class Camera {
    public:
        Camera(Window& window, glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
        ~Camera();

        glm::mat4 getProjection() const;

        glm::mat4 calculateViewMatrix();

        void update();
        void MoveCameraForwards();
        void MoveCameraBackwards();
        void MoveCameraLeft();
        void MoveCameraRight();
    private:
        float fovy, aspect, zNear, zFar;
        glm::mat4 projection;

        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
        glm::vec3 worldUp;

        float yaw;
        float pitch;

        float movementSpeed;
        float turnSpeed;
};
