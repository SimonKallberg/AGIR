//
//  Sphere.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

//Classes
#include "Geometry.hpp"
#include "vec3.hpp"
#include "Ray.hpp"
//Libraries
#include <cmath>
#include <stdio.h>


class Sphere : public Geometry {
public:
    Sphere(vec3 inC = vec3(1.0f, 1.0f, 0.0f), float inR =  1.0f, vec3 inColor = vec3(1.0f, 1.0f, 1.0f), Material refType = OREN_NAYAR, float inRoughness = 1.0f)
      : r(inR), centerPos(inC), objectColor(inColor), objectMaterial(refType) { }

    void flipNormal();
    vec3 calcNormal(Ray &ray);
    bool rayIntersection(Ray &ray) override;
    glm::vec3 color() override;
    Material material() override;
    float roughness() override;
    
private:
    Material objectMaterial;
    vec3 objectColor = vec3(1.0f);
    float objectRoughness;
    float r = 1.0f;
    vec3 centerPos = vec3(0.0f);
    vec3 normal = vec3(0.0f);
};

#endif /* Sphere_hpp */
