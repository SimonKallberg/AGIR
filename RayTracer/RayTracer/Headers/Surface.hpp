//
//  Surface.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-02.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Surface_hpp
#define Surface_hpp

#include <stdio.h>
#include "Ray.hpp"
#include "Vector3.hpp"

Vector3 calcPerfectReflection(Ray &inRay, Vector3 normal);


class Surface {
  
public:
	Surface(int reflection = 0, ColorDbl col = ColorDbl(1,1,1)) 
		: reflectionType(reflection), color(col) 
	{	}
	ColorDbl diffuseReflection(ColorDbl inC);
	ColorDbl specularReflection(ColorDbl inC);
	int reflectionType;
	ColorDbl color;

	double reflectionCo = 0.8;

};

#endif /* Surface_hpp */
