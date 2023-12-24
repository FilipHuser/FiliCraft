//
//  Camera.cpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#include "Camera.hpp"

Camera::Camera()
{
    CameraConfig cc;
    
    this->cc = cc;
    this->eye = cc.eye;
    this->cen = cc.cen;
    this->up = cc.up;
    
    this->viewMatrix = glm::lookAt(eye , cen , up);
    this->projectionMatrix = glm::perspective(cc.fov , cc.aspectRatio , cc.zNear , cc.zFar);
    
    notify(this);
}

void Camera::moveForward()
{
    glm::vec3 forward = glm::normalize(this->cen - this->eye);
    
    this->eye += forward * cc.cameraSpeed;
    this->cen += forward * cc.cameraSpeed;
    
    this->viewMatrix = glm::lookAt(eye , cen , up);
    notify(this);
}

void Camera::moveBack()
{
    glm::vec3 backward = glm::normalize(this->cen - this->eye);
    
    this->eye -= backward * cc.cameraSpeed;
    this->cen -= backward * cc.cameraSpeed;
    
    this->viewMatrix = glm::lookAt(eye , cen , up);
    notify(this);
}

void Camera::moveRight()
{
    glm::vec3 right = glm::normalize(glm::cross(this->cen - this->eye, this->up));
    
    this->eye -= right * cc.cameraSpeed;
    this->cen -= right * cc.cameraSpeed;
    
    this->viewMatrix = glm::lookAt(eye , cen , up);
    notify(this);
}

void Camera::moveLeft()
{
    glm::vec3 left = glm::normalize(glm::cross(this->cen - this->eye, this->up));
    
    this->eye += left * cc.cameraSpeed;
    this->cen += left * cc.cameraSpeed;
    
    this->viewMatrix = glm::lookAt(eye , cen , up);
    notify(this);
}

void Camera::lookAround(float deltaX, float deltaY) {
    // Adjust the yaw and pitch angles based on mouse input
    cc.yaw += deltaX * this->cc.cameraSpeed;
    cc.pitch += deltaY * this->cc.cameraSpeed;

    // Ensure pitch stays within the range of [-89, 89] degrees to avoid gimbal lock
    if (cc.pitch > 89.0f) cc.pitch = 89.0f;
    if (cc.pitch < -89.0f) cc.pitch = -89.0f;

    // Calculate new target direction vector
    glm::vec3 newTarget;
    newTarget.x = cos(glm::radians(cc.yaw)) * cos(glm::radians(cc.pitch));
    newTarget.y = sin(glm::radians(cc.pitch));
    newTarget.z = sin(glm::radians(cc.yaw)) * cos(glm::radians(cc.pitch));
    this->cen = this->eye + glm::normalize(newTarget);

    // Update the up vector if needed
    this->up = glm::vec3(0.0f, 1.0f, 0.0f); // Set to default up vector
    
    this->viewMatrix = glm::lookAt(this->eye , this->cen , this->up);
    notify(this);
}

