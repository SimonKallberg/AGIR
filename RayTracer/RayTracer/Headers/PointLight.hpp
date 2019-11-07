//
//  PointLight.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-01.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <stdio.h>
#include "glm.hpp"

using namespace glm;
using namespace std;

class PointLight {
public:
    PointLight(vec3 inC = vec3(1.0f, 1.0f, 0.0f))
      : pos(inC) { }

    vec3 pos = vec3(0.0f, 0.0f, 0.0f);
};


#endif /* PointLight_hpp */
