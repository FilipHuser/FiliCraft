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

#include "ShaderLoader.hpp"

class ShaderProgram
{
public:
    ShaderProgram(GLint vertexShader , GLint fragmentShader);
    
    void use() { glUseProgram(this->shaderProgramID); }
    void un_use() { glUseProgram(0); }
    
private:
    GLint shaderProgramID;
};

#endif /* ShaderProgram_hpp */
