//
//  Ray.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Ray.hpp"

//Copy constructor - deep copy
Ray::Ray (const Ray &old_obj) {
    //Check for null pointers
    start = (old_obj.start != nullptr) ? new vec3(*old_obj.start) : nullptr;
    end = (old_obj.end != nullptr) ? new vec3(*old_obj.end) : nullptr;
    intSectPoint = (old_obj.intSectPoint != nullptr) ? new vec3(*old_obj.intSectPoint) : nullptr;

    
    //TODO fix dangling pointers
    endTri = old_obj.endTri;
    endSphere = old_obj.endSphere;
    color = old_obj.color;
}

Ray::~Ray() {

    delete reflectedRay;
    delete monteCarloRay;

    monteCarloRay = nullptr;
    reflectedRay = nullptr;
    start = nullptr;
    end = nullptr;
    endTri = nullptr;
    endSphere = nullptr;
}

void Ray::sortIntersections() {
    //Sort the intersections by length of vector
    sort(intSectPoints.begin(), intSectPoints.end(),
        [](const intersection & a, const intersection & b) -> bool
    {
        return a.distance < b.distance;
    });
    
}


std::ostream& operator<<(std::ostream& out, const Ray& v1) {
    out << "Ray: starting point: ";
    if (v1.start != nullptr) {
        out << glm::to_string(*v1.start);
    }
    out  << " end point: " ;
    if (v1.end != nullptr) {
        out << glm::to_string(*v1.end);
    }
    out << " intersection point: ";
    if (v1.intSectPoint != nullptr) {
        out << glm::to_string(*v1.intSectPoint);
    }
    out <<  std::endl;
	return out;
}
