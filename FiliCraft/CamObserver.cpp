//
//  CamObserver.cpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#include "CamObserver.hpp"

void CamObserver::update(Subject * s)
{
    if(Camera* cam = dynamic_cast<Camera*>(s))
    {
        this->sp->set_viewMatrix(cam->get_vm());
        this->sp->set_projectionMatrix(cam->get_pm());
    }
}
