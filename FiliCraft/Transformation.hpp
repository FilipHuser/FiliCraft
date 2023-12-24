//
//  Transformation.hpp
//  FiliCraft
//
//  Created by Filip Huser on 16.12.2023.
//

#ifndef Transformation_hpp
#define Transformation_hpp
#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
    virtual void apply(glm::mat4& modelMatrix) = 0;
};

#endif /* Transformation_hpp */
