//
//  Pixel.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Pixel.hpp"

Pixel & Pixel::operator=(vec3 p)
{
    color = p;
    
	return *this;
}
