//
//  Observer.hpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#ifndef Observer_hpp
#define Observer_hpp
#pragma once

class Subject;

class Observer {
public:
    virtual void update(Subject * s) = 0;
};

#endif /* Observer_hpp */
