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


vec3 Sphere::calcNormal(Ray &ray) {
    
    normal = normalize(*ray.intSectPoint - centerPos);
    return normal;
}
/*
bool Sphere::rayIntersection(Ray &p)
{
    //Start point
    vec3 o = *p.start;
    
    //Normalized vec3 from starting point
    vec3 I = normalize(*p.end-*p.start);

    float a = 1.0f;
    float b = dot((2.0f*I),o-centerPos);
    float c = dot(o-centerPos, o-centerPos) - (r*r);
    
    float d1 = (-b/2.0f) - sqrt(((b/2.0f)*(b/2.0f))-(a*c));
    float d2 = (-b/2.0f) + sqrt(((b/2.0f)*(b/2.0f))-(a*c));
    
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
    
   // d = d1 > 0.0f ? d1 : d2;

    //Check with distance if we got a hit
    if (d < 0.01f || d > 1000.0f) return false;
    
    
    vec3 intersection = o + I * d;
//    glm::vec3 normal = glm::normalize(intersection - this->centerPos);
    
    //Check if ray is inside sphere
//     if(p.inside)
//            if (glm::dot(vec3(*p.end-*p.start), normal) > 0.0f) return false;
    
    
    float distance = length(intersection-*p.start);
    p.intSectPoints.push_back({vec3(intersection), distance , nullptr, this});
    return true;
}
*/

bool Sphere::rayIntersection(Ray &ray)
{
    vec3 o = *ray.start;
    vec3 l = normalize(*ray.end - *ray.start);
    float a = 1.0f;
    float b = dot((o - centerPos), (l * 2.0f));
    float c = dot((o - centerPos), (o - centerPos)) - r * r;
    
    float discriminant = (b*b/4) - a*c;
    if (discriminant > 0)
    {
        float d0 = - (b/2) - sqrt(discriminant);
        float d1 = - (b/2) + sqrt(discriminant);
        
        float d = d0 > 0.01 ? d0 : d1;
        
        //if (d > ray.t) return false;
        
        if (d > 0.01)
        {
            //ray.t = d;
            vec3 intersection = o + l * d;
            //normal = (ray.intersection - center) * (1 / radius);
            //ray.intersection = ray.intersection + ray.objectNormal * 0.0001;
            
            float distance = length(intersection-*ray.start);
            ray.intSectPoints.push_back({vec3(intersection), distance , nullptr, this});

            return true;
        }
    }
    
    return false;
}
