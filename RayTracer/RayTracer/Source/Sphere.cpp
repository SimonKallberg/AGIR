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
    if(d1 < 0.1f && d2 < 0.1f) {
        return false;
    }
    
    if(d1 > d2) {
        vec3 x2 = o + d2*I;
        float distance = (x2-*p.start).length();
        p.intSectPoints.push_back({vec3(x2), distance , nullptr, this});
        return true;
    }
    else {
        vec3 x1 = o + d1*I;
        float distance = length(x1-*p.start);
        p.intSectPoints.push_back({vec3(x1), distance , nullptr, this});
        return true;
    }
}
