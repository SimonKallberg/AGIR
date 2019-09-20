//
//  Vertex.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include "Vertex.hpp"

class Vertex {
public:
    Vertex(double inX, double inY, double inZ, double inW = 1.0)
    : x(inX), y(inY), z(inZ), w(inW) {}
    double x, y, z, w;
    friend Vertex operator+(Vertex lhs, Vertex rhs);
    friend Vertex operator-(Vertex lhs, Vertex rhs);
};

#endif /* Vertex_hpp */
