//
//  ColorDbl.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef ColorDbl_hpp
#define ColorDbl_hpp

#include <stdio.h>

class ColorDbl {
public:
    double r, g, b;
    
    ColorDbl(double inR, double inG, double inB)
    : r(inR), g(inG), b(inB){}
};

#endif /* ColorDbl_hpp */
