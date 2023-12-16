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
    this->shaderProgramID = glCreateProgram();
    glAttachShader(this->shaderProgramID, fragmentShader);
    glAttachShader(this->shaderProgramID, vertexShader);
    glLinkProgram(this->shaderProgramID);
    
    test_compile(this->shaderProgramID);
}
