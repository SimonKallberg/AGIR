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
#include "Vertex.hpp"
#include "ColorDbl.hpp"
#include "Ray.hpp"

class Sphere {
public:
    Sphere(Vertex inC, double inR, ColorDbl inColor)
      : r(inR), centerPos(inC), color(inColor) { }
    bool rayIntersection(Ray p);
    double r = 1.0;
    Vertex centerPos = Vertex(Vector3(0.0,0.0,0.0));
    ColorDbl color = ColorDbl(1.0,1.0,1.0);
};

#endif /* Sphere_hpp */
