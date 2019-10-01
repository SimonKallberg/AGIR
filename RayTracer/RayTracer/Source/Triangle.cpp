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
    double length = normal.length();
    normal = Vector3(normal/length);
    //std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;
}

bool Triangle::rayIntersection(Ray &p)
{
    Vector3 T = (*p.start-v0).vec3;
    Vector3 E1 = (v1-v0).vec3;
    Vector3 E2 = (v2-v0).vec3;
    Vector3 D = (*p.end - *p.start).vec3;
    Vector3 P = crossProduct(D, E2);
    Vector3 Q = crossProduct(T, E1);
    Vector3 tuv = Vector3(dotProduct(Q, E2)/dotProduct(P, E1),
                                       dotProduct(P, T)/dotProduct(P, E1),
                                       dotProduct(Q, D)/dotProduct(P, E1));
    
    //Check if variables are in triangle area -> intersection!
    if( ((tuv.y + tuv.z <= 1) && (tuv.y >= 0) && (tuv.z >= 0)) && (tuv.x > 1) &&
      ((((tuv.y*(v1-v0)) + (tuv.z*(v2-v0)) - (tuv.x*(*p.end-*p.start)) - (*p.start-v0)) < 0.0001) ||
      (((tuv.y*(v1-v0)) + (tuv.z*(v2-v0)) - (tuv.x*(*p.end-*p.start)) - (*p.start-v0)) > 0.0001))) {
            //cout << "intersection!" << endl;
            p.endTri = this;
            p.intSectPoint = new Vertex(tuv.x*D.x, tuv.x*D.y ,tuv.x*D.z);
            //*p.intSectPoint = *p.intSectPoint + *p.start;
            return true;
    }
    return false;
}


