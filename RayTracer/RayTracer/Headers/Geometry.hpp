//
//  Geometry.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-11-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include "glm.hpp"
#include "Ray.hpp"

using namespace glm;

enum Material{
    LAMBERTIAN,
    REFLECTIVE,
    TRANSPARENT,
    EMISSIVE
};

class Geometry {
public:
    virtual ~Geometry() = 0; //Pure virtual class
    virtual bool rayIntersection(Ray &ray) = 0;
    //virtual vec3 getNormal() = 0;
};

#endif /* Geometry_hpp */
