//
//  Sphere.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "vec3.hpp"
#include "Ray.hpp"
#include <cmath>
#include "Surface.hpp"

class Sphere {
public:
    Sphere(vec3 inC = vec3(1.0f, 1.0f, 0.0f), float inR =  1.0f, vec3 inColor = vec3(1.0f, 1.0f, 1.0f), int refType = 0, float inRoughness = 0.0f)
      : r(inR), centerPos(inC), color(inColor), surf(refType, inColor, inRoughness) { }

    void flipNormal();
    vec3 calcNormal(Ray &p);
    bool rayIntersection(Ray &p);
    float r = 1.0f;
    vec3 centerPos = vec3(0.0f, 0.0f ,0.0f);
    vec3 color = vec3(1.0f, 1.0f, 1.0f);
    vec3 normal = vec3(0.0f);
    Surface surf;
};

#endif /* Sphere_hpp */
