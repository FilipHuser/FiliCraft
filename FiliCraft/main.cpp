//
//  main.cpp
//  FiliCraft
//
//  Created by Filip Huser on 06.12.2023.
//

#include <iostream>

#include "FiliCraft.hpp"
#include "ShaderLoader.hpp"

int main(int argc, const char * argv[]) 
{
    FiliCraft fc;
    
    fc.GLFW_init();
    fc.create_window(1200, 900, "Filicraft");
    fc.GLEW_init();
    fc.run();
    
    
    
    return 0;
}
