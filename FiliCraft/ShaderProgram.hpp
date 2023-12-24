//
//  ShaderProgram.hpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp
#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.hpp"

class ShaderProgram
{
public:
    ShaderProgram(GLint vertexShader , GLint fragmentShader);
    
    void use() { glUseProgram(this->shaderProgramID); }
    void un_use() { glUseProgram(0); }
    
    void send_uniforms();
    
    void set_viewMatrix(glm::mat4 vm) { this->viewMatrix = vm; }
    void set_projectionMatrix(glm::mat4 pm) { this->projectionMatrix = pm; };
    
    GLint get_uniformLoc(GLchar* name) { return glGetUniformLocation(this->shaderProgramID , name); }
    
private:
    GLint shaderProgramID;
    
//uniforms
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
//locations
    GLint viewMatrixLoc;
    GLint projectionMatrixLoc;
};

#endif /* ShaderProgram_hpp */
