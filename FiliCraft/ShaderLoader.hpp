//
//  ShaderLoader.hpp
//  FiliCraft
//
//  Created by Filip Huser on 08.12.2023.
//

#ifndef ShaderLoader_hpp
#define ShaderLoader_hpp
#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>

class ShaderLoader {
public:
    ShaderLoader() = default;
    GLuint loadShader(std::string path , GLenum shaderType);
};

#endif /* ShaderLoader_hpp */
