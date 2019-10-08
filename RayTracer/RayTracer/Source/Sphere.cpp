//
//  Sphere.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Sphere.hpp"
#include <cmath>

Vector3 Sphere::calcNormal(Ray &p) {
    
    Vector3 normal = p.intSectPoint->vec3 - centerPos.vec3;
    normal.normalize();
    return normal;
}

bool Sphere::rayIntersection(Ray &p)
{
    //Start point
    Vector3 o = (*p.start).vec3;
    
    //Normalized Vector3 from starting point
    Vector3 I = (*p.end-*p.start).vec3;
    I.normalize();

    double a = 1.0;
    double b = dotProduct((2*I),o-centerPos.vec3);
    double c = dotProduct(o-centerPos.vec3, o-centerPos.vec3) - (r*r);
    
    double d1 = (-b/2) + sqrt(((b/2)*(b/2))-(a*c));
    double d2 = (-b/2) - sqrt(((b/2)*(b/2))-(a*c));
    
    //Check if root is imaginary - then the ray doesn't intersect
    if(isnan(d1) || isnan(d2)) {
        return false;
    }
    //Check if point is same as starting point - then the ray doesn't intersect
    if(d1 < 0.0001 && d2 < 0.0001) {
        return false;
    }
    
    if(d1 > d2) {
        Vector3 x2 = o + d2*I;
        p.intSectPoint = new Vertex(x2);
        p.endSphere = this;
        return true;
    }
    else {
       Vector3 x1 = o + d1*I;
        p.intSectPoint = new Vertex(x1);
        p.endSphere = this;
        return true;
    }
    
    
    
    
    
    
    
//    //Check if x1 or x2 is on the sphere's surface & starting point of ray isn't on spheres surface
//    if(abs((x1-centerPos.vec3).length()*(x1-centerPos.vec3).length() - r*r) < 0.001){

//    }
//    else if ((abs((x2-centerPos.vec3).length()*(x2-centerPos.vec3).length() - r*r) < 0.001)){

//    }
//    else {
//        return false;
//    }
}
