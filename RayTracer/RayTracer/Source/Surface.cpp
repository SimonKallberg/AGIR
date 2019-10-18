//
//  Surface.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-02.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Surface.hpp"

//Schlicks equation for reflection coefficient
double getReflectionCoeff(Vector3 &R, Vector3 &T, double n1, double n2) {
    double angle = acos(dotProduct(R,T)/(R.length()*T.length()));
    double R0 = ((n1-n2)/(n1+n2))*((n1-n2)/(n1+n2));
    double reflCoeff = R0 + ((1-R0)*pow(1-cos(angle), 5));
    return reflCoeff;
}

//Schlicks equation for transmission coefficient
double getTransmissCoeff(Vector3 &R, Vector3 &T, double n1, double n2) {
    return (1-getReflectionCoeff(R, T, n1, n2));
}



//Snell's law of refraction
Vector3 calcRefraction(Ray &inRay, Vector3 normal, double n1, double n2) {
    
    Vector3 I = (*inRay.end - *inRay.start).vec3;
    I.normalize();
    Vector3 T = (n1/n2)*I + normal*((-1*(n1/n2)*(dotProduct(normal, I)))
                -sqrt(1-(n1/n2)*(n1/n2)*(1-(dotProduct(normal, I)*dotProduct(normal, I)))));
    
    //From thick to thin medium, e.g. air into glass
    if(n1 < n2) {
        T.normalize();
        return T;
    }
    else {
        //Angle between incoming ray and normal
        double alpha = acos(dotProduct(I,normal)/(I.length()*normal.length()));
        //Brewster angle
        double alpham = acos(n2/n1);
        
        //No refraction exists!
        if(alpha > alpham) {
            return Vector3(0,0,0);
        }
        
    }
    
    return normal;
}

ColorDbl Surface::diffuseReflection(ColorDbl inC)
{
	return (inC * (reflectionCo/3.1415));
}

ColorDbl Surface::specularReflection(ColorDbl inC)
{
	return inC;
}
