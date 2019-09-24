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
    
    ColorDbl(double inR, double inG, double inB)
    : r(inR), g(inG), b(inB){}

	ColorDbl& operator=(ColorDbl temp);

	friend std::ostream& operator<<(std::ostream& out, const ColorDbl& v1);
};

#endif /* ColorDbl_hpp */
