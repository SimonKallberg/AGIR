//
//  Triangle.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>

class Triangle {
public:
    Vertex v0, v1, v2;
    ColorDbl color;
    Direction normal = Direction(0.0,0.0,0.0);
    
    Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inCol = ColorDbl(0.0,0.0,0.0))
    : v0(inV0), v1(inV1), v2(inV2), color(inCol)
    {
        normal = calcNormal();
    }
    bool rayIntersection(Ray arg1);
    Direction calcNormal();
    
};

#endif /* Triangle_hpp */
