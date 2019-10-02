//
//  Triangle.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Triangle.hpp"

std::ostream& operator<<(std::ostream& out, const Triangle& v1) {
	out << v1.v0 << " " << v1.v1 << " " << v1.v2 << std::endl;
	return out;
}

Vector3 Triangle::calcNormal() {
    Vector3 vector1 = Vector3(v0.vec3-v1.vec3);
    Vector3 vector2 = Vector3(v0.vec3-v2.vec3);
    //Cross product to get normal
    Vector3 normal = crossProduct(vector1, vector2);
    //Normalize
    normal.normalize();
    //std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;
}

bool Triangle::rayIntersection(Ray &p)
{
    //Start ray
    Vector3 T = (*p.start-v0).vec3;
    //Edge 1
    Vector3 E1 = (v1-v0).vec3;
    //Edge 2
    Vector3 E2 = (v2-v0).vec3;
    //Direction
    Vector3 D = (*p.end - *p.start).vec3;
    D.normalize();
    //Edge normal
    Vector3 P = crossProduct(D, E2);
    //Determinant
    double determinant = dotProduct(P, E1);
    
    if(abs(determinant) < 0.001 ) {
        return false;
    }
    
    Vector3 Q = crossProduct(T, E1);
    
    double t = dotProduct(Q, E2)/determinant;
    double u = dotProduct(T, P)/determinant;
    double v = dotProduct(D, Q)/determinant;
    
    //Check if variables are in triangle area -> intersection!
    if(u < 0.0 || u > 1.0) {
        return false;
    }
    
    if(v < 0.0 || u + v > 1.0) {
        return false;
    }
    
    if(t > 0.0001 || t < 1000000) {

        p.endTri = this;
        Vector3 intersection = p.start->vec3 + t*D;
        p.intSectPoint = new Vertex(intersection);
        return true;
    }
    return false;
}


