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
    vec3 normal = cross(vector2, vector1);
    //Normalize
    normalize(normal);

    return normal;
}

bool Triangle::rayIntersection(Ray &p)
{
    //Start ray
    vec3 T = (*p.start-v0);
    //Edge 1
    vec3 E1 = (v1-v0);
    //Edge 2
    vec3 E2 = (v2-v0);
    //Direction
    vec3 D = (*p.end - *p.start);
    normalize(D);
    //Edge normal
    vec3 P = cross(D, E2);
    //Determinant
    float determinant = dot(P, E1);
    
    if(abs(determinant) < 0.001f ) {
        return false;
    }
    
    vec3 Q = cross(T, E1);
    
    float t = dot(Q, E2)/determinant;
    float u = dot(T, P)/determinant;
    float v = dot(D, Q)/determinant;
    
    //Check if variables are in triangle area -> intersection!
    if(u < 0.0f || u > 1.0f) {
        return false;
    }
    
    if(v < 0.0f || u + v > 1.0f ) {
        return false;
    }
    
    if(t > 0.00000001f && t < 1000000.0f) {
        vec3 intersection = *p.start + (t*D);
        float distance = length(intersection - *p.start);
        p.intSectPoints.push_back({intersection, distance, this, nullptr});
        return true;
    }
    return false;
}

void Triangle::flipNormal() {
    normal = -1.0f*normal;
}

