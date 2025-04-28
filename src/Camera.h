#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

enum CameraDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    Camera(glm::vec3 position, float yaw = -90.0f, float pitch = 0.0f);
    ~Camera();

    void keyboardInput(CameraDirection direction, float deltaTime);
    void mouseInput(float offsetX, float offsetY);
    void mouseScroll(float offsetY);

    glm::mat4 getViewMatrix();

    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed = 5.0f;
    float mouseSensitivity = 0.1f;
    float zoom = 45.0f;
private:
    void updateCameraVectors();
};
