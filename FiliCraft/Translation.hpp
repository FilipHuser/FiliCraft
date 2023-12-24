//
//  Translation.hpp
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

class Translation : public Transformation {
public:
    Translation(float translateX, float translateY, float translateZ)
        : translateX(translateX), translateY(translateY), translateZ(translateZ) {}

    void apply(glm::mat4& modelMatrix) override {
        modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX, translateY, translateZ));
    }

private:
    float translateX, translateY, translateZ;
};

#endif /* Translation_hpp */

