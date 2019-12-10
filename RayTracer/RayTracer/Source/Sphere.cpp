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
            vec3 normal = normalize(intersection - centerPos);
            float distance = length(intersection-*ray.start);
            ray.intSectPoints.push_back({vec3(intersection), distance , nullptr, this, this, normal});

            return true;
        }
    }
    
    return false;
}

Material Sphere::material(){
    return objectMaterial;
}

vec3 Sphere::color(){
    return objectColor;
}

float Sphere::roughness() {
    return objectRoughness;
}
