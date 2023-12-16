//
//  Mesh.hpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

enum VDS //Vertex Data Structure
{
    xyz,                //pos
    xyz_ccc,            //pos + color
    xyz_nnn,            //pos + normal
    xyz_ccc_nnn,        //pos + color + normal
    xyz_nnn_uv          //pos + normal + textureCoord
};

class Mesh
{
public:
    Mesh(std::vector<float> vertexData , VDS vds_type , GLenum primitiveType);

    void init();
    
    void create_VBO();
    void create_VAO();
    void create_EBO();
    
    void render();
    
private:
    VDS vds_type;                       //Vertex data structure type
    GLuint VBO;                         //Vertex Buffer Object
    GLuint VAO;                         //Vertex Array Object
    GLuint EBO;                         //Element Buffer Object
    std::vector<float> vertexData;      //Vertex data
    GLenum primitiveType;               //Primitive type
};

#endif /* Mesh_hpp */
