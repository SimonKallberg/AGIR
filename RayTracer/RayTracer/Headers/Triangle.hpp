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
#include "glm.hpp"

using namespace std;
using namespace glm;

class Scene;

class Triangle {
public:
    
    vec3 color = vec3(1.0f, 0.0f, 0.0f);
	vec3 v0, v1, v2 = vec3(0.0f, 0.0f, 0.0f);;
	vec3 normal = vec3(0.0f, 0.0f, 0.0f);
    Surface surf;
    
	Triangle(vec3 inV0 = vec3(1.0f, 1.0f, 0.0f), vec3 inV1 = vec3(1.0f, -1.0f, 0.0f), vec3 inV2 = vec3(-1.0f, -1.0f, 0.0f), vec3 inCol = vec3(0.5f, 0.5f, 0.5f), int refType = 0, float inRoughness = 0.0f)
		: v0(inV0), v1(inV1), v2(inV2), surf(refType, inCol, inRoughness), color(inCol)
	{
		normal = calcNormal();
	}

	bool rayIntersection(Ray &arg1);
	vec3 calcNormal();
    void flipNormal();

	friend ostream& operator<<(ostream& out, const Triangle& v);
    
};

#endif
