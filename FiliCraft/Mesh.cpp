//
//  Mesh.cpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#include "Mesh.hpp"

Mesh::Mesh(std::vector<float> vertexData , VDS vds_type , GLenum primitiveType) : vertexData(vertexData) , vds_type(vds_type) , primitiveType(primitiveType)
{
    init();
}

void Mesh::init()
{
    create_VBO();
    create_VAO();
    create_EBO();
}

void Mesh::create_VBO()
{
    glGenBuffers(1 , &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER , this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(float) , this->vertexData.data() , GL_STATIC_DRAW);
}

void Mesh::create_VAO()
{
    switch (this->vds_type) 
    {
        case xyz:
            
            glGenVertexArrays(1, &this->VAO); // Generate the VAO
            glBindVertexArray(this->VAO); // Bind the VAO

            // Bind the VBO to GL_ARRAY_BUFFER target
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            // Specify the layout of the vertex data
            // First, the position data (three components)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

            // Unbind the VBO (not necessary, but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Unbind the VAO
            glBindVertexArray(0);
            break;
            
        case xyz_nnn:
            glGenVertexArrays(1, &this->VAO); // Generate the VAO
            glBindVertexArray(this->VAO); // Bind the VAO

            // Bind the VBO to GL_ARRAY_BUFFER target
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            // Specify the layout of the vertex data
            // First, the position data (three components)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);

            // Next, the normal data (three components)
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));

            // Unbind the VBO (not necessary, but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Unbind the VAO
            glBindVertexArray(0);
            break;
            
        case xyz_nnn_uv:
            glGenVertexArrays(1, &this->VAO); // Generate the VAO
            glBindVertexArray(this->VAO); // Bind the VAO

            // Bind the VBO to GL_ARRAY_BUFFER target
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            // Specify the layout of the vertex data
            // First, the position data (three components)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);

            // Next, the normal data (three components)
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
            
            // Next, the uv data (two components)
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));

            // Unbind the VBO (not necessary, but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Unbind the VAO
            glBindVertexArray(0);
            break;
    }
}

void Mesh::create_EBO()
{
    
}

void Mesh::render()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(this->primitiveType, 0, this->vertexData.size());
    // Unbind the VAO
    glBindVertexArray(0);
}
