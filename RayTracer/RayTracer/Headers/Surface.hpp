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
Vector3 calcRefraction(Ray &inRay, Vector3 normal, double n1, double n2);
double getReflectionCoeff(Vector3 &R, Vector3 &T, double n1, double n2);


class Surface {
  
public:
	Surface(int inReflectionType = 0, ColorDbl col = ColorDbl(1,1,1))
		: reflectionType(inReflectionType), color(col) 
	{	}
	ColorDbl diffuseReflection(ColorDbl inC);
	ColorDbl specularReflection(ColorDbl inC);
    //Diffuse reflection = 0, Perfect refraction = 1
	int reflectionType = 0;
	ColorDbl color;

	double reflectionCo = 0.8;

};

#endif /* Surface_hpp */
