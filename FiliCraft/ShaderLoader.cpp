//
//  ShaderLoader.cpp
//  FiliCraft
//
//  Created by Filip Huser on 08.12.2023.
//

#include "ShaderLoader.hpp"

bool compile(GLint shader)
{
    glCompileShader(shader);
    
    GLint compileStatus;
    
    glGetShaderiv(shader , GL_COMPILE_STATUS, &compileStatus);
    
    if (compileStatus != GL_TRUE) { return 1; }
    
    return 0; //OK
}

GLuint ShaderLoader::loadShader(std::string path , GLenum shaderType)
{
    std::ifstream file_stream(path);

    if (!file_stream.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return -1;
    }

    std::string source_code((std::istreambuf_iterator<char>(file_stream)),
                               std::istreambuf_iterator<char>());

    file_stream.close();
    
    GLuint shaderID = glCreateShader(shaderType);
    
    const char* source = source_code.c_str();
    
    glShaderSource(shaderID , 1, &source, NULL);
    
    if(compile(shaderID))
    {
        std::cerr << "Shader compilation error ! Shader: " << path << std::endl;
        return -2;
    }
    

    return shaderID;
}
