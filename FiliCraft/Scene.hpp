//
//  Scene.hpp
//  FiliCraft
//
//  Created by Filip Huser on 24.12.2023.
//

#ifndef Scene_hpp
#define Scene_hpp
#pragma once

#include <vector>

#include "DrawableObj.hpp"
#include "Light.hpp"

class Scene {
public:
    Scene(std::vector<DrawableObj> objects , std::vector<Light> lights) : objects(objects) , lights(lights) {}
        
    std::vector<DrawableObj> objects;
    std::vector<Light> lights;
};

#endif /* Scene_hpp */
