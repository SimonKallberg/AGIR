//
//  Surface.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-02.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Surface.hpp"

Vector3 calcPerfectReflection(Ray &inRay, Vector3 normal) {
    Vector3 I = (*inRay.end - *inRay.start).vec3;
    I.normalize();
    
    return (I - 2*(dotProduct(I,normal)*normal));
}

//Snell's law of refraction
Vector3 calcRefraction(Ray &inRay, Vector3 normal, double n1, double n2) {
    Vector3 I = (*inRay.end - *inRay.start).vec3;
    Vector3 T = (n1/n2)*I + normal*((-1*(n1/n2)*(dotProduct(normal, I)))
                -sqrt(1-(n1/n2)*(n1/n2)*(1-(dotProduct(normal, I)*dotProduct(normal, I)))));
    T.normalize();
    
    return T;
}

ColorDbl Surface::diffuseReflection(ColorDbl inC)
{
	return (inC * (reflectionCo/3.1415));
}

ColorDbl Surface::specularReflection(ColorDbl inC)
{
	return inC;
}
