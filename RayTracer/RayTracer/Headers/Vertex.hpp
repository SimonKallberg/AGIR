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
#include <iostream>
#include "Vector3.hpp"
#include "glm.hpp"

using namespace glm;
using namespace std;

class Vertex {
public:
    Vector3 vec3;
    double w;
    
    Vertex(double inX, double inY, double inZ, double inW = 1.0)
        : vec3(inX, inY, inZ), w(inW) {}
	Vertex(Vector3 inVec, double inW = 1.0)
		: vec3(inVec) {}
    //Copy constructor
    Vertex (const Vertex &old_obj) {
        vec3 = old_obj.vec3;
        w = old_obj.w;
    }
    //Conversion from vec3
    Vertex& operator=(Vector3 inVec)
    {
        vec3 = inVec;
        w = 1.0;
        return *this;
    }

	friend Vertex operator+(Vertex lhs, Vertex rhs);
    friend Vertex operator*(double lhs, Vertex rhs);
    friend Vertex operator*(Vertex lhs, double rhs);
	friend Vertex operator-(Vertex lhs, Vertex rhs);
    friend bool operator<(Vertex lhs, double rhs);
    friend bool operator>(Vertex lhs, double rhs);

	friend std::ostream& operator<<(std::ostream& out, const Vertex& v1);
};

#endif /* Vertex_hpp */
