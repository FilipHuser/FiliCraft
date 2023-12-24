//
//  Rotation.hpp
//  FiliCraft
//
//  Created by Filip Huser on 21.12.2023.
//

#ifndef Translation_hpp
#define Translation_hpp

#include "Transformation.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public Transformation {
public:
    Rotation(float angle , glm::vec3 originalVector , glm::vec3 axisOfRotation) : angle(glm::radians(angle)) , originalVector(originalVector) , axisOfRotation(axisOfRotation) {}

    void apply(glm::mat4& modelMatrix) override {
        //modelMatrix = glm::rotate(originalVector, angle, axisOfRotation);

    }

private:
    float angle;
    glm::vec3 originalVector;
    glm::vec3 axisOfRotation;
    
};

#endif /* Translation_hpp */

