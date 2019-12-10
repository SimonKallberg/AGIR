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
#include "Geometry.hpp"

using namespace std;
using namespace glm;

class Triangle;
class Sphere;

struct intersection {
    vec3 interSectPoint = vec3(0.0f);
    float distance = -1.0f;
    Geometry* object = nullptr;
    vec3 normal = vec3(0.0f);
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
    Ray* reflectedRay = nullptr;
    Ray* refractedRay = nullptr;
    Ray* diffuseRay = nullptr;

    //Pointing towards verticees
	vec3* start = nullptr;
	vec3* end = nullptr;
    vec3* intSectPoint = nullptr;
    
    //Intersecting objects
    vector<intersection> intSectPoints;
    Geometry* endObject = nullptr;
    vec3 objectNormal = vec3(0.0f);
    float length = -1.0f;

	friend ostream& operator<<(ostream& out, const Ray& v1);
};

#endif
