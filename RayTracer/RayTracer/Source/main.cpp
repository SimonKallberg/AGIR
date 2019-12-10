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

int main()
{
    //Create scene & setup room
	Scene myScene;
    myScene.initialize();
    
	//Add objects
    //myScene.addTetrahedron(vec3(7.0f, -2.0f, 0.0f), 2.5f, vec3(1.0f, 1.0f, 1.0f), DIFFUSE, 1.0f);
    myScene.addSphere(vec3(6.0f, 2.0f, 2.5f), 0.5f, vec3(0.5f, 0.5f, 0.5f), TRANSPARENT);
    myScene.addSphere(vec3(10.0f, -2.0f, 1.0f), 1.0f, vec3(1.0f, 1.0f, 1.0f), DIFFUSE, 0.0f);
    myScene.addSphere(vec3(10.0f, 2.0f, 1.0f), 1.0f, vec3(1.0f, 1.0f, 1.0f), DIFFUSE, 1.0f);
    myScene.addSphere(vec3(7.0f, 0.0f, -3.0f), 2.0f, vec3(0.5f, 0.5f, 0.5f), SPECULAR);
    
    //Add an area light
    myScene.addAreaLight(vec3(5.0f, -2.0f, 4.5f), vec3(5.0f, 2.0f, 4.5f), vec3(7.0f, 2.0f, 4.5f), vec3(7.0f, -2.0f, 4.5f));
    
    //Render & save image
	Camera myCamera(&myScene);
	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}
