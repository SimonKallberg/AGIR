//
//  Ray.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>

class Vertex;
class Triangle;
class ColorDbl;

class Ray {
public:
    Vertex* start;
    Vertex* end;
    Vertex* intSectPoint;
    
    Triangle* endTri;
    ColorDbl color;
};

#endif /* Ray_hpp */
