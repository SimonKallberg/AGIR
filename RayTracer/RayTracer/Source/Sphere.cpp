//
//  Sphere.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Sphere.hpp"

bool Sphere::rayIntersection(Ray p)
{
    //Start point
    Vector3 o = (*p.start).vec3;
    //Normalized Vector3 from starting point
    Vector3 I = (*p.end-*p.start).vec3;
    //Normalize I
    I = I/I.length();
    double a = 1.0;
 //   double b = dotProduct(2*I,o-centerPos);
//    Vector3 D = *p.end - *p.start;
//    Vector3 P = crossProduct(D, E2);
//    Vector3 Q = crossProduct(T, E1);
//    Vector3 tuv = Vector3(dotProduct(Q, E2)/dotProduct(P, E1),
//                                       dotProduct(P, T)/dotProduct(P, E1),
//                                       dotProduct(Q, D)/dotProduct(P, E1));
//
//    //Check if variables are in triangle area -> intersection!
//    if( ((tuv.y + tuv.z <= 1) && (tuv.y >= 0) && (tuv.z >= 0)) && (tuv.x > 1) &&
//      ((((tuv.y*(v1-v0)) + (tuv.z*(v2-v0)) - (tuv.x*(*p.end-*p.start)) - (*p.start-v0)) < 0.0001) ||
//      (((tuv.y*(v1-v0)) + (tuv.z*(v2-v0)) - (tuv.x*(*p.end-*p.start)) - (*p.start-v0)) > 0.0001))) {
//            //cout << "intersection!" << endl;
//            p.endTri = this;
//            p.intSectPoint = new Vertex(tuv.x*D.x, tuv.x*D.y ,tuv.x*D.z);
//            *p.intSectPoint = *p.intSectPoint + *p.start;
//            return true;
//    }
    return false;
}
