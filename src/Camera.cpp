#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float yaw, float pitch) {
    this -> yaw = yaw;
    this -> pitch = pitch;
    this -> position = position;
    this -> front = {0.0f, 0.0f, -1.0f};
    this -> worldUp = {0.0f, 1.0f, 0.0f};

    this -> updateCameraVectors();
}

Camera::~Camera() {

}

void Camera::keyboardInput(CameraDirection direction, float deltaTime) {
    float velocity = this -> movementSpeed * deltaTime;

    glm::vec3 flatFront = glm::normalize(glm::vec3(this -> front.x, 0.0f, this -> front.z));
    glm::vec3 flatRight = glm::normalize(glm::vec3(this -> right.x, 0.0f, this -> right.z));

    switch (direction) {
        case FORWARD:
            this -> position += flatFront * velocity;
            break;
        case BACKWARD:
            this -> position -= flatFront * velocity;
            break;
        case LEFT:
            this -> position -= flatRight * velocity;
            break;
        case RIGHT:
            this -> position += flatRight * velocity;
            break;
        case UP:
            this -> position.y += velocity;
            break;
        case DOWN:
            this -> position.y -=  velocity;
            break;
    }
}

void Camera::mouseInput(float offsetX, float offsetY) {
    offsetX *= this -> mouseSensitivity;
    offsetY *= this -> mouseSensitivity;

    this -> yaw += offsetX;
    this -> pitch += offsetY;

    if (this -> pitch > 89.0f) {
        this -> pitch = 89.0f;
    } else if (this -> pitch < -89.0f) {
        this -> pitch = -89.0f;
    }

    this -> updateCameraVectors();
}

void Camera::mouseScroll(float offsetY) {
    this -> zoom -= offsetY;

    if (this -> zoom < 1.0f) {
        this -> zoom = 1.0f;
    } else if (this -> zoom > 45.0f) {
        this -> zoom = 45.0f;
    }
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(this -> position, this -> position + this -> front, this -> up);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;

    front.x = cos(glm::radians(this -> yaw)) * cos(glm::radians(this -> pitch));
    front.y = sin(glm::radians(this -> pitch));
    front.z = sin(glm::radians(this -> yaw)) * cos(glm::radians(this -> pitch));

    this -> front = glm::normalize(front);

    this -> right = glm::normalize(glm::cross(this -> front, this -> worldUp));
    this -> up = glm::normalize(glm::cross(this -> right, this -> front));
}
