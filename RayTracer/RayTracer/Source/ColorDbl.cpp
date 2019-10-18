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

ColorDbl operator*(ColorDbl lhs, double rhs)
{
	return ColorDbl(lhs.r*rhs, lhs.g*rhs, lhs.b*rhs);
}

ColorDbl & ColorDbl::operator=(const ColorDbl &temp)
{
	r = temp.r;
	g = temp.g;
	b = temp.b;
	return *this;
}

ColorDbl operator+(ColorDbl lhs, ColorDbl rhs) {
    return ColorDbl(lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b);
}

ColorDbl operator-(ColorDbl lhs, ColorDbl rhs) {
    return ColorDbl(lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b);
}
ColorDbl operator*(double lhs, ColorDbl rhs) {
    return ColorDbl(lhs*rhs.r, lhs*rhs.g, lhs*rhs.b);
}
