//
//  main.cpp
//  AGIR
//
//  Created by Ylva Selling & Simon Källberg on 2019-09-20.
//  Copyright © 2019 Ylva Bajsing. All rights reserved.

const int DIFFUSE = 0;
const int SPECULAR = 1;
const int TRANSPARENT = 2;

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

int main()
{
	Scene myScene;
    //Setup room
    myScene.initialize();
    
	//Adding a tetrahedron
    myScene.addTetrahedron(Vertex(7.0, 3.0, -2.0), 2, ColorDbl(0.9, 0.1, 0.7), DIFFUSE);
    //myScene.addTetrahedron(Vertex(7.0, 2.0, 0.0), 1, ColorDbl(0.5, 0.5, 0.5));
    
    //Adding a sphere
    myScene.addSphere(Vertex(5.0, -2.0, -3.0), 2.0, ColorDbl(0.5, 0.5, 0.5), TRANSPARENT);
    myScene.addPointLight(Vertex(5.0,0.0,4.5));
	Camera myCamera(&myScene);

	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}
