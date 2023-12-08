//
//  FiliCraft.hpp
//  FiliCraft
//
//  Created by Filip Huser on 07.12.2023.
//

#ifndef FiliCraft_hpp
#define FiliCraft_hpp

#pragma once

//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FiliCraft {
public:
    FiliCraft() = default;
    
    void create_window();
    void run();
    
private:
};

#endif /* FiliCraft_hpp */
