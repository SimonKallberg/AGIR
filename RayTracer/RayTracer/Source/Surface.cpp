//
//  Surface.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-02.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Surface.hpp"

//Schlicks equation for reflection coefficient
float getReflectionCoeff(vec3 &R, vec3 &T, float n1, float n2) {
    float angle = acos(dot(R,T)/length(R)*length(T));
    float R0 = ((n1-n2)/(n1+n2))*((n1-n2)/(n1+n2));
    float reflCoeff = R0 + ((1.0f-R0)*pow(1.0f-cos(angle), 5.0f));
    return reflCoeff;
}

//Schlicks equation for transmission coefficient
float getTransmissCoeff(vec3 &R, vec3 &T, float n1, float n2) {
    return (1.0f-getReflectionCoeff(R, T, n1, n2));
}



//Snell's law of refraction
vec3 calcRefraction(Ray &inRay, vec3 normal, float n1, float n2) {
    
    vec3 I = normalize(*inRay.end - *inRay.start);

    vec3 T = (n1/n2)*I + normal*((-1.0f*(n1/n2)*(dot(normal, I)))
                -sqrt(1.0f-(n1/n2)*(n1/n2)*(1.0f-(dot(normal, I)*dot(normal, I)))));
    
    //From thick to thin medium, e.g. air into glass
    if(n1 < n2) {
        normalize(T);
        return T;
    }
    else {
        //Angle between incoming ray and normal
        float alpha = glm::acos(dot(I,normal)/(length(I)*length(normal)));
        //Brewster angle
        float alpham = glm::acos(n2/n1);
        
        //No refraction exists!
        if(alpha > alpham) {
            return vec3(0.0f,0.0f,0.0f);
        }
    }
    
    return normal;
}

//vec3 Surface::diffuseReflection(vec3 inC)
//{
//	return (inC * (reflectionCo/3.1415f));
//}

//vec3 Surface::specularReflection(vec3 inC)
//{
//	return inC;
//}
