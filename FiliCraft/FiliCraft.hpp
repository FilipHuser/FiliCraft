//
//  FiliCraft.hpp
//  FiliCraft
//
//  Created by Filip Huser on 07.12.2023.
//

#ifndef FiliCraft_hpp
#define FiliCraft_hpp

#pragma once

#include <iostream>

//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <memory.h>

#include "Camera.hpp"
#include "ShaderLoader.hpp"
#include "Mesh.hpp"
#include "DrawableObj.hpp"
#include "CamObserver.hpp"

//#include "Translation.hpp"
//#include "Scale.hpp"
//#include "Rotation.hpp"


#include <string>

class FiliCraft {
public:
    FiliCraft();
    
    void GLFW_init();
    void GLEW_init();
    
    void create_window(int width , int height , const char* title);
    void run();
    
private:
    GLFWwindow* window;
    int frameBuffer_width;
    int frameBuffer_height;
    
    std::unique_ptr<Camera> cam;
};

#endif /* FiliCraft_hpp */
