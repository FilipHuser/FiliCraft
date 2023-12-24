//
//  Scale.hpp
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

class Scale : public Transformation {
public:
    Scale(float scaleX, float scaleY, float scaleZ)
        : scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ) {}

    void apply(glm::mat4& modelMatrix) override {
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, scaleY, scaleZ));
    }

private:
    float scaleX, scaleY, scaleZ;
};

#endif /* Translation_hpp */


