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

Vector3 calcPerfectReflection(Ray &inRay, Vector3 normal) {
    Vector3 I = (*inRay.end - *inRay.start).vec3;
    I.normalize();
    
    return (I - 2*(dotProduct(I,normal)*normal));
}

//Snell's law of refraction
Vector3 calcRefraction(Ray &inRay, Vector3 normal, double n1, double n2) {
	bool inside = false;
	if (dotProduct(normal, inRay.end->vec3 - inRay.start->vec3) > 0) {
		inside = true;
	}
	if (inside) {
		normal = -1 * normal;
	}


    //std::cout << "n1: " << n1 << " n2: " << n2 << std::endl;
    Vector3 I = (*inRay.end - *inRay.start).vec3;
    I.normalize();
    double r = n1/n2;
    double c = dotProduct(normal, I);
    double k = 1-((r*r)*(1-(c*c)));
	Vector3 T = Vector3(0, 0, 0);
	if (k < 0) {
		return Vector3(0, 0, 0);
	}
	else {
		T = r * I - normal * (r*c + sqrt(k));
		T.normalize();
	}

    
    if(dotProduct(normal, I) < 0) {
        //cout << "flip the normal" << endl;
        c = -c;
    }
    else {
        std::swap(n1, n2);
        normal = -1*normal;
    }
    
    Vector3 T = r*I + normal * (r*c - sqrt(k));
    T.normalize();
    
    //From thick to thin medium, e.g. glass into air
    /*if(k < 0) {
        //Angle between incoming ray and normal
//        double alpha = acos(dotProduct(I,normal)/(I.length()*normal.length()));
//        
//        //Brewster angle
//        double alpham = atan(n2/n1);
//        
//        //No refraction exists!
//        if(alpha > alpham) {
//            std::cout << "No refraction exists!" << std::endl;
//            return calcPerfectReflection(inRay, normal);
//        }
        std::cout << "k < 0" << std::endl;
        return Vector3(0,0,0);
    }*/
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
