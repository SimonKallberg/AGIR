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

Direction Triangle::calcNormal() {
    Direction vector1 = Direction(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
    Direction vector2 = Direction(v0.x-v2.x, v0.y-v2.y, v0.z-v2.z);
    //Cross product to get normal
    Direction normal = crossProduct(vector1, vector2);
    //Normalize
    double length = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    normal = Direction(normal.x/length, normal.y/length, normal.z/length);
    //std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;
}

bool Triangle::rayIntersection(Ray p)
{
    Direction T = *p.start-v0;
    Direction E1 = v1-v0;
    Direction E2 = v2 - v0;
    Direction D = *p.end - *p.start;
    Direction P = crossProduct(D, E2);
    Direction Q = crossProduct(T, E1);
    Direction intersection = Direction(dotProduct(Q, E2)/dotProduct(P, E1),
                                       dotProduct(P, T)/dotProduct(P, E1),
                                       dotProduct(Q, D)/dotProduct(P, E1));
    //Check if variables are in triangle area -> intersection!
    if(intersection.y + intersection.z < 1 && intersection.y >= 0 && intersection.z >= 0) {
        p.endTri = this;
        return true;
    }
    return false;
}

