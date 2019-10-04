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
#include "Vertex.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"
#include "ColorDbl.hpp"
#include "Surface.hpp"
#include <cmath>

using namespace std;

class Scene;

class Triangle {
public:
	Vertex v0, v1, v2;
	ColorDbl color;
	Vector3 normal = Vector3(0.0, 0.0, 0.0);
    Surface surf;

	Triangle(Vertex inV0 = Vertex(1.0, 1.0, 0.0), Vertex inV1 = Vertex(1.0, -1.0, 0.0), Vertex inV2 = Vertex(-1.0, -1.0, 0.0), ColorDbl inCol = ColorDbl(0.5, 0.5, 0.5))
		: v0(inV0), v1(inV1), v2(inV2), color(inCol)
	{
		normal = calcNormal();
	}

	bool rayIntersection(Ray &arg1);
	Vector3 calcNormal();
    void flipNormal();

	friend std::ostream& operator<<(std::ostream& out, const Triangle& v1);
    
};

#endif
