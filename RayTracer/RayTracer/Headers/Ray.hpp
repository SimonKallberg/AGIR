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

class Vertex;
class Triangle;
class ColorDbl;

class Ray {
public:
	Ray(Vertex* s, Vertex* e)
		: start(s), end(e)
	{}
    
    //Copy constructor
    Ray (const Ray &old_obj) {
        start = old_obj.start;
        end = old_obj.end;
        intSectPoint = old_obj.intSectPoint;
        endTri = old_obj.endTri;
        color = old_obj.color;
    }

	Vertex* start;
	Vertex* end;
	Vertex* intSectPoint = nullptr;

	Triangle* endTri = nullptr;
	ColorDbl color = ColorDbl(0.0, 0.0, 0.0);

	friend std::ostream& operator<<(std::ostream& out, const Ray& v1);
};

#endif
