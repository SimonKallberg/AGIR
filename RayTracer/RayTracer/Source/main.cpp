//
//  main.cpp
//  AGIR
//
//  Created by Ylva Selling & Simon Källberg on 2019-09-20.
//  Copyright © 2019 Ylva Bajsing. All rights reserved.
/*
const int DIFFUSE = 0;
const int SPECULAR = 1;
const int TRANSPARENT = 2;
const float ROUGH = 3.0f;
*/
//STD libraries
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

//Classes
#include "Triangle.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Geometry.hpp"

//External libraries
#include "matrix.hpp"
#include "bitmap_image.hpp"
#include "glm.hpp"
#include "transform.hpp"
#include "ext.hpp"

using namespace std;

vec3 calcRefraction(Ray &inRay, vec3 normal, float n1, float n2);
float getReflectionCoeff(vec3 &R, vec3 &T, float n1, float n2);

int main()
{
    //Create scene & setup room
	Scene myScene;
    myScene.initialize();
    
	//Add objects
    //Arguments: Position vec3, Scale float, Color vec3, Material type, Roughness float
    //myScene.addTetrahedron(vec3(7.0f, -2.0f, 0.0f), 2.5f, vec3(1.0f, 1.0f, 1.0f), DIFFUSE, 1.0f);
    myScene.addSphere(vec3(6.0f, 2.0f, 2.5f), 0.5f, vec3(0.5f, 0.5f, 0.5f), TRANSPARENT);
    myScene.addSphere(vec3(10.0f, -2.0f, 1.0f), 1.0f, vec3(1.0f, 1.0f, 1.0f), LAMBERTIAN, 0.0f);
    myScene.addSphere(vec3(10.0f, 2.0f, 1.0f), 1.0f, vec3(1.0f, 1.0f, 1.0f), OREN_NAYAR, 1.0f);
    myScene.addSphere(vec3(7.0f, 0.0f, -3.0f), 2.0f, vec3(0.5f, 0.5f, 0.5f), REFLECTIVE);
    
    //Add an area light
    myScene.addAreaLight(vec3(5.0f, -2.0f, 4.5f), vec3(5.0f, 2.0f, 4.5f), vec3(7.0f, 2.0f, 4.5f), vec3(7.0f, -2.0f, 4.5f));
    
    //Render & save image
	Camera myCamera(&myScene);
	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}

//Schlicks equation for reflection coefficient
float getReflectionCoeff(vec3 &R, vec3 &T, float n1, float n2) {
    float angle = acos(dot(R,T)/length(R)*length(T));
    float R0 = ((n1-n2)/(n1+n2))*((n1-n2)/(n1+n2));
    float reflCoeff = R0 + ((1.0f-R0)*pow(1.0f-cos(angle), 5.0f));
    return reflCoeff;
}

//Schlicks equation for transmission coefficient
float getTransmissCoeff(vec3 &R, vec3 &T, float n1, float n2) {
    return (1.0f-getReflectionCoeff(R, T, n1, n2));
}

//Snell's law of refraction
vec3 calcRefraction(Ray &inRay, vec3 normal, float n1, float n2) {
    
    vec3 I = normalize(*inRay.end - *inRay.start);

    vec3 T = (n1/n2)*I + normal*((-1.0f*(n1/n2)*(dot(normal, I)))
                -sqrt(1.0f-(n1/n2)*(n1/n2)*(1.0f-(dot(normal, I)*dot(normal, I)))));
    
    //From thick to thin medium, e.g. air into glass
    if(n1 < n2) {
        normalize(T);
        return T;
    }
    else {
        //Angle between incoming ray and normal
        float alpha = glm::acos(dot(I,normal)/(length(I)*length(normal)));
        //Brewster angle
        float alpham = glm::acos(n2/n1);
        
        //No refraction exists!
        if(alpha > alpham) {
            return vec3(0.0f,0.0f,0.0f);
        }
    }
    return normal;
}
