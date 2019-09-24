//
//  Pixel.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Pixel.hpp"

Pixel & Pixel::operator=(Pixel p)
{
	color.r = p.color.r;
	color.g = p.color.g;
	color.b = p.color.b;
	return *this;
}
