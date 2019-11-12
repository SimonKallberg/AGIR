//
//  Sphere.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Sphere.hpp"
#include <cmath>

void Sphere::flipNormal() {
    normal = -1.0f*normal;
}


vec3 Sphere::calcNormal(Ray &p) {
    
    normal = normalize(*p.intSectPoint - centerPos);
    return normal;
}

bool Sphere::rayIntersection(Ray &p)
{
    //Start point
    vec3 o = *p.start;
    
    //Normalized vec3 from starting point
    vec3 I = normalize(*p.end-*p.start);

    float a = 1.0f;
    float b = dot((2.0f*I),o-centerPos);
    float c = dot(o-centerPos, o-centerPos) - (r*r);
    
    float d1 = (-b/2.0f) + sqrt(((b/2.0f)*(b/2.0f))-(a*c));
    float d2 = (-b/2.0f) - sqrt(((b/2.0f)*(b/2.0f))-(a*c));
    
    //Check if root is imaginary - then the ray doesn't intersect
    if(isnan(d1) || isnan(d2)) {
        return false;
    }
    //Check if point is same as starting point - then the ray doesn't intersect
    if(d1 < FLT_EPSILON && d2 < FLT_EPSILON) {
        return false;
    }
    
    float d = 0.0f;
    
    if (d1 <= 0 && d2 <= 0) return false;
    else if (d1 < 0) d = d2;
    else if (d2 < 0) d = d1;
    else if (d1 < d2) d = d1;
    else d = d2;

    //Check with distance if we got a hit
    if (d < FLT_EPSILON || d > 1000.0f) return false;
    
    
    vec3 intersection = o + I * d;
    glm::vec3 normal = glm::normalize(intersection - this->centerPos);
    
    //Check if ray is inside sphere
     if(p.inside)
            if (glm::dot(vec3(*p.end-*p.start), normal) > 0.0f) return false;
    
    
    float distance = length(intersection-*p.start);
    p.intSectPoints.push_back({vec3(intersection), distance , nullptr, this});
    return true;
}

