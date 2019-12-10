//
//  Triangle.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Triangle.hpp"

std::ostream& operator<<(std::ostream& out, const Triangle& v) {
	out << to_string(v.v0) << " " << to_string(v.v1) << " " << to_string(v.v2) << std::endl;
	return out;
}

vec3 Triangle::calcNormal() {
    vec3 vector1 = vec3(v0-v1);
    vec3 vector2 = vec3(v0-v2);
    //Cross product to get normal
    vec3 normal = normalize(cross(vector2, vector1));
    
    return normal;
}

bool Triangle::rayIntersection(Ray &ray)
{
    //Start ray
    vec3 T = (*ray.start-v0);
    //Edge 1
    vec3 E1 = (v1-v0);
    //Edge 2
    vec3 E2 = (v2-v0);
    //Direction
    vec3 D = normalize(*ray.end - *ray.start);
    //Edge normal
    vec3 P = cross(D, E2);
    //Determinant
    float determinant = dot(P, E1);
    
    if(abs(determinant) < 0.00001f ) {
        return false;
    }
    float invDet = 1.0f/determinant;
    
    vec3 Q = cross(T, E1);
    
    float t = dot(Q, E2)*invDet;
    float u = dot(T, P)*invDet;
    float v = dot(D, Q)*invDet;
    
    //Check if variables are in triangle area -> intersection!
    if(u < 0.f || u > 1.f) {
        return false;
    }
    
    if(v < 0.f || u + v > 1.f ) {
        return false;
    }
    
    if(t > 0.001f && t < 1000000.0f) {
        vec3 intersection = *ray.start + (t*D);
        float distance = glm::length(intersection - *ray.start);
        ray.intSectPoints.push_back({intersection, distance, this, nullptr, this});
        return true;
    }
    return false;
}

void Triangle::flipNormal() {
    normal = -1.0f*normal;
}

