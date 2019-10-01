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


class Triangle;
class ColorDbl;
class Sphere;

class Ray {
public:
	Ray(Vertex* s, Vertex* e)
		: start(s), end(e)
	{}
    
    //Copy constructor - deep copy
    Ray (const Ray &old_obj);
    ~Ray();

	Vertex* start = nullptr;
	Vertex* end = nullptr;
	Vertex* intSectPoint = nullptr;

	Triangle* endTri = nullptr;
    Sphere* endSphere = nullptr;
	ColorDbl color = ColorDbl(0.0, 0.0, 0.0);

	friend std::ostream& operator<<(std::ostream& out, const Ray& v1);
};

#endif
