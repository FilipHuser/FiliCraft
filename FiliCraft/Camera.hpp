//
//  Camera.hpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#ifndef Camera_hpp
#define Camera_hpp
#pragma once

#include "Subject.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct CameraConfig
{
    glm::vec3 eye = glm::vec3(0.0 , 0.0, 5.0);
    glm::vec3 cen = glm::vec3(0.0 , 0.0, 0.0);
    glm::vec3 up = glm::vec3(0.0 , -1.0, 0.0);
//------------------------------------------
    GLfloat zNear = 0.01f;
    GLfloat zFar = 100.0f;
    GLfloat aspectRatio = 1.5f;
//------------------------------------------
    GLfloat cameraSpeed = 0.05f;
    GLfloat yaw = -89.0f;   // Yaw is initialized to -90 degrees because a yaw of 0 degrees points initially to the left.
    GLfloat pitch = 0.0f;
    GLfloat fov = 30.0f;
};

class Camera : public Subject
{
public:
    Camera();
    
    void moveForward();
    void moveBack();
    void moveRight();
    void moveLeft();
    
    void lookAround(float deltaX, float deltaY);
    
    glm::mat4 get_vm() { return this->viewMatrix; }
    glm::mat4 get_pm() { return this->projectionMatrix; }
    
private:
    glm::vec3 eye;
    glm::vec3 cen;
    glm::vec3 up;
    
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    
    CameraConfig cc;
};

#endif /*Camera_hpp*/
