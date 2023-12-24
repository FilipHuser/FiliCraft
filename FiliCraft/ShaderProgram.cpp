//
//  ShaderProgram.cpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#include "ShaderProgram.hpp"

bool test_compile(GLint shaderProgramID)
{
    GLint status;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        return 1;
    }
    return 0;
}

ShaderProgram::ShaderProgram(GLint vertexShader , GLint fragmentShader)
{
    this->viewMatrix = glm::lookAt(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,-1,0));
    this->projectionMatrix = glm::perspective(30.0, 1.5, 0.01, 100.0);
    
    this->shaderProgramID = glCreateProgram();
    glAttachShader(this->shaderProgramID, fragmentShader);
    glAttachShader(this->shaderProgramID, vertexShader);
    glLinkProgram(this->shaderProgramID);
    
    test_compile(this->shaderProgramID);
    
    this->viewMatrixLoc = glGetUniformLocation(this->shaderProgramID, "viewMatrix");
    this->projectionMatrixLoc = glGetUniformLocation(this->shaderProgramID, "projectionMatrix");
}

void ShaderProgram::send_uniforms()
{
    glUniformMatrix4fv(this->viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->viewMatrix)); //VM
    glUniformMatrix4fv(this->projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix)); //PM
}
