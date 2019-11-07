//
//  Pixel.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Pixel_hpp
#define Pixel_hpp

#include <stdio.h>
#include "ColorDbl.hpp"
#include "Vertex.hpp"
#include "Ray.hpp"
#include <vector>
#include "glm.hpp"

class Pixel {
public:
    Pixel(vec3 inCol)
		: color(inCol) {}
    Pixel(float r = 0.0f, float g = 0.0f, float b = 0.0f)
    : color(r, g, b) {}


    vec3 color;
    Ray* ray = nullptr;

	Pixel& operator=(vec3 p);
};

#endif
