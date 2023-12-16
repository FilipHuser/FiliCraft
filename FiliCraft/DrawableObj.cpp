//
//  DrawableObj.cpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#include "DrawableObj.hpp"

void DrawableObj::display()
{
    this->sp.use();
    this->mesh.render();
    this->sp.un_use();
}
