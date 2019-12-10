//
//  Geometry.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-12-10.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp


#include <stdio.h>
#include "Surface.hpp"

class Ray;
/*
enum Material{
    LAMBERTIAN,
    OREN_NAYAR,
    REFLECTIVE,
    TRANSPARENT,
    EMISSIVE
};
*/
class Geometry {
public:
    
    virtual ~Geometry() = 0;
 //   virtual Material material() = 0;
    virtual bool rayIntersection(Ray &ray) = 0;
};

#endif /* Geometry_hpp */
