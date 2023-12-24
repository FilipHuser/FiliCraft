//
//  Subject.cpp
//  FiliCraft
//
//  Created by Filip Huser on 20.12.2023.
//

#include "Subject.hpp"

void Subject::notify(Subject * s)
{
    std::for_each(observers.begin(), observers.end(), [&](Observer * o)
                                                      {
                                                            o->update(s);
                                                      });
}
