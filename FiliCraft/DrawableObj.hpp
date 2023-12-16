//
//  DrawableObj.hpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#ifndef DrawableObj_hpp
#define DrawableObj_hpp
#pragma once

#include <iostream>

#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>

class DrawableObj {
public:
    DrawableObj(Mesh mesh , ShaderProgram sp) : mesh(mesh) , sp(sp) , modelMatrix(glm::mat4(1.0)) {};
    
    void display();
    
    
    
private:
    Mesh mesh;
    ShaderProgram sp;
    glm::mat4 modelMatrix;
};

#endif /* DrawableObj_hpp */
