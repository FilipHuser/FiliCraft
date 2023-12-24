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
#include <glm/glm.hpp>
#include <vector>

#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Transformation.hpp"
#include "Material.hpp"

class DrawableObj {
public:
    DrawableObj(Mesh mesh , ShaderProgram* sp , Material material) : mesh(new Mesh(mesh)) , sp(sp) , modelMatrix(glm::mat4(1.0)) , material(material) {};
    DrawableObj(Mesh mesh , ShaderProgram* sp , Transformation* t ,  Material material);
    
    void display();
    
private:
    Mesh* mesh;
    ShaderProgram* sp;
    
    glm::mat4 modelMatrix;
    
    std::vector<Transformation*> transformations;
    
    Material material;
};

#endif /* DrawableObj_hpp */
