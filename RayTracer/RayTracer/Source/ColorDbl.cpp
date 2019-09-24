//
//  ColorDbl.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "ColorDbl.hpp"

std::ostream & operator<<(std::ostream & out, const ColorDbl & v1)
{
	out << "r: " << v1.r << " g: " << v1.g << " b: " << v1.b << std::endl;
	return out;
}

ColorDbl & ColorDbl::operator=(ColorDbl temp)
{
	r = temp.r;
	g = temp.g;
	b = temp.b;
	return *this;
}
