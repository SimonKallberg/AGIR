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


class Triangle;
class ColorDbl;
class Sphere;

struct intersection {
    Vertex interSectPoint;
    double distance = 0;
    Triangle* tri;
    Sphere* sphere;
};

class Ray {
public:
	Ray(Vertex* s, Vertex* e)
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

    //Pointing towards vertexes
	Vertex* start = nullptr;
	Vertex* end = nullptr;
    Vertex* intSectPoint = nullptr;
    
    //Intersecting objects
    std::vector<intersection> intSectPoints;
	Triangle* endTri = nullptr;
    Sphere* endSphere = nullptr;
	ColorDbl color = ColorDbl(0.0, 0.0, 0.0);
    
    //Refraction index
    double refractionIndex = 1;

	friend std::ostream& operator<<(std::ostream& out, const Ray& v1);
};

#endif
