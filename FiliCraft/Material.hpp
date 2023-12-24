//
//  Material.hpp
//  FiliCraft
//
//  Created by Filip Huser on 22.12.2023.
//

#ifndef Material_hpp
#define Material_hpp
#pragma once

#include <glm/glm.hpp>

#define RED glm::vec3(1.0 , 0.0 , 0.0)
#define GREEN glm::vec3(0.0 , 1.0 , 0.0)
#define BLUE glm::vec3(1.0 , 0.0 , 1.0)
#define WHITE glm::vec3(1.0 , 1.0 , 1.0)


class Material {
public:
    Material(glm::vec3 color , float shininess) : color(color) , shininess(shininess) {};
    
    glm::vec3 color;
    float shininess;
};

#endif /* Material_hpp */
