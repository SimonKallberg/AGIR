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
#include "Vertex.hpp"
#include "ColorDbl.hpp"
#include <iostream>
#include <vector>
#include "glm.hpp"
#include "string_cast.hpp"
#include <algorithm>	

using namespace std;
using namespace glm;

class Triangle;
class ColorDbl;
class Sphere;

struct intersection {
    vec3 interSectPoint = vec3(0.0f,0.0f,0.0f);
    float distance = -1.0f;
    Triangle* tri = nullptr;
    Sphere* sphere = nullptr;
};

class Ray {
public:
	Ray(vec3* s, vec3* e)
		: start(s), end(e)
	{}
    
    //Copy constructor - deep copy
    Ray (const Ray &old_obj);
    ~Ray();
    
    void sortIntersections();
    
    //Tree structure
    Ray* parent = nullptr;
    Ray* reflectedRay = nullptr;
    Ray* refractedRay = nullptr;
    Ray* monteCarloRay = nullptr;

    //Pointing towards vertexes
	vec3* start = nullptr;
	vec3* end = nullptr;
    vec3* intSectPoint = nullptr;
    
    //Intersecting objects
    vector<intersection> intSectPoints;
	Triangle* endTri = nullptr;
    Sphere* endSphere = nullptr;
	vec3 color = vec3(0.0f, 0.0f, 0.0f);

	friend ostream& operator<<(ostream& out, const Ray& v1);
};

#endif
