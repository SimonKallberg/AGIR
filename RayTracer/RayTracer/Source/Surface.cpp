//
//  Surface.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-02.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Surface.hpp"

Vector3 calcPerfectReflection(Ray &inRay, Vector3 normal) {
    Vector3 I = (*inRay.end - *inRay.start).vec3;
    I.normalize();
    
    return (I - 2*(dotProduct(I,normal)*normal));
}
