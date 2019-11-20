//
//  main.cpp
//  AGIR
//
//  Created by Ylva Selling & Simon Källberg on 2019-09-20.
//  Copyright © 2019 Ylva Bajsing. All rights reserved.

const int DIFFUSE = 0;
const int SPECULAR = 1;
const int TRANSPARENT = 2;
const float ROUGH = 3.0f;

#include <iostream>
#include <vector>
#include <cstdio>
#include "bitmap_image.hpp"
#include "Triangle.hpp"
#include "Ray.hpp"
#include "matrix.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include <string>
#include "Sphere.hpp"
#include "glm.hpp"
#include "transform.hpp"
#include "ext.hpp"

using namespace std;



int main()
{
	Scene myScene;
    //Setup room
    myScene.initialize();
    
	//Adding a tetrahedron
    myScene.addTetrahedron(vec3(7.0f, -1.0f, 0.0f), 2.0f, vec3(0.5f, 0.5f, 0.5f), TRANSPARENT, 0.0f);
    
    //Adding a sphere
    myScene.addSphere(vec3(6.0f, -2.0f, -2.5f), 0.5f, vec3(0.5f, 0.5f, 0.5f), TRANSPARENT, 0.0f);
    //Adding a sphere
    myScene.addSphere(vec3(5.0f, 1.0f, 1.0f), 1.0f, vec3(0.5f, 0.2f, 0.2f), TRANSPARENT,  0.0f);
    //Adding a sphere
    myScene.addSphere(vec3(9.0f, 2.0f, -3.0f), 2.0f, vec3(0.5f, 0.5f, 0.5f), SPECULAR);
    myScene.addPointLight(vec3(5.0f,0.0f,4.5f));
//    myScene.addPointLight(vec3(6.0f,0.0f,4.5f));
//    myScene.addPointLight(vec3(4.0f,0.0f,4.5f));
    myScene.addAreaLight(vec3(5.0f, -2.0f, 4.5f), vec3(5.0f, 2.0f, 4.5f), vec3(7.0f, 2.0f, 4.5f), vec3(7.0f, -2.0f, 4.5f));
	Camera myCamera(&myScene);
    
	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}
