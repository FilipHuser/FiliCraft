//
//  DrawableObj.cpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#include "DrawableObj.hpp"

DrawableObj::DrawableObj(Mesh mesh , ShaderProgram* sp , Transformation* t ,  Material material) : mesh(new Mesh(mesh)) , sp(sp) , modelMatrix(glm::mat4(1.0)) , material(material)
{
    this->transformations.push_back(t);
};

void DrawableObj::display()
{
    this->sp->use();
    this->sp->send_uniforms();
    
    for (auto& transformation : this->transformations)
    {
        transformation->apply(this->modelMatrix);
    }
    
    if(transformations.size() > 0) { transformations.clear(); }
    
    glUniformMatrix4fv(this->sp->get_uniformLoc("modelMatrix"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix)); //MM
    glUniform3fv(this->sp->get_uniformLoc("objColor"), 1, glm::value_ptr(this->material.color));
    
    this->mesh->render();
    this->sp->un_use();
}
