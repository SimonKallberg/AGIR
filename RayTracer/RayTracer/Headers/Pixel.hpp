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

class Pixel {
public:
    Pixel(ColorDbl inCol) 
		: color(inCol.r, inCol.g, inCol.b) {}
    Pixel(double r = 0, double g = 0, double b = 0)
    : color(r, g, b) {}


    ColorDbl color;
    Ray* ray = nullptr;

	Pixel& operator=(Pixel p);
};

#endif
