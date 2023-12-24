//
//  Subject.hpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#ifndef Subject_hpp
#define Subject_hpp
#pragma once

#include "Observer.hpp"

#include <vector>

class Subject {
public:
    void attach(Observer* o) { this->observers.push_back(o); };
    virtual void notify(Subject * s);
    
private:
    std::vector<Observer*> observers;
};

#endif /* Subject_hpp */
