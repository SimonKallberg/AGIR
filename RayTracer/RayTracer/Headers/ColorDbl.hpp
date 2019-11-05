//
//  ColorDbl.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef ColorDbl_hpp
#define ColorDbl_hpp

#include <stdio.h>
#include <iostream>

class ColorDbl {
public:
    double r, g, b;
    
    ColorDbl(double inR = 0.0, double inG = 0.0, double inB = 0.0)
    : r(inR), g(inG), b(inB){}

    //Assignment operator
    ColorDbl& operator=(const ColorDbl &temp);
    friend ColorDbl operator+(ColorDbl lhs, ColorDbl rhs);
    friend ColorDbl operator-(ColorDbl lhs, ColorDbl rhs);
    friend ColorDbl operator*(double lhs, ColorDbl rhs);
    
    //Copy constructor
    ColorDbl (const ColorDbl &old_obj) {
        r = old_obj.r;
        g = old_obj.g;
        b = old_obj.b;
    }

	friend std::ostream& operator<<(std::ostream& out, const ColorDbl& v1);
	friend ColorDbl operator*(ColorDbl lhs, double rhs);
};

#endif /* ColorDbl_hpp */
