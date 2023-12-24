//
//  CamObserver.hpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#ifndef CamObserver_hpp
#define CamObserver_hpp
#pragma once

#include "CamObserver.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"


class CamObserver : public Observer
{
public:
    CamObserver(ShaderProgram * sp) : sp(sp) {}
    
//----- Observer -----
    void update(Subject * s)override;
    
private:
    ShaderProgram* sp;
};

#endif /* CamObserver_hpp */
