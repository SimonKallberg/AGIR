//
//  main.cpp
//  AGIR
//
//  Created by Ylva Selling & Simon Källberg on 2019-09-20.
//  Copyright © 2019 Ylva Bajsing. All rights reserved.


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
	myScene.initialize();
    //Adding a red tetrahedron
    //myScene.addTetrahedron(Vertex(8.0, 0, 0), Vertex(8, -4, -4.0), Vertex(10, 0, -4.0), Vertex(8, 4, -4.0), ColorDbl(1.0, 0.0, 0.0));
    //Adding a grey sphere
    myScene.addSphere(Vertex(8.0,0.0,-4.0), 2.0, ColorDbl(0.5, 0.5, 0.5));
    myScene.addPointLight(Vertex(13.0,0.0,4.0));
	Camera myCamera(&myScene);


	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}
