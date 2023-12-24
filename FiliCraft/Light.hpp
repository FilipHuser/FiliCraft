//
//  Light.hpp
//  FiliCraft
//
//  Created by Filip Huser on 24.12.2023.
//

#ifndef Light_hpp
#define Light_hpp
#pragma once

#include <glm/glm.hpp>

enum LightType {
    POINT,
    DIRECTIONAL
};

class Light {
public:
    Light(int id , LightType lt , glm::vec3 pos , glm::vec3 color) : id(id) , lt(lt) , pos(pos) , color(color) {}
    
    int id;
    LightType lt;
    glm::vec3 pos;
    glm::vec3 color;
};

#endif /* Light_hpp */
