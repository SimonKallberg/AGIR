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
#include "matrix.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include <string>


int main()
{
	Scene myScene;
	myScene.initialize();
    //Vertex(10,-6,0), Vertex(13,0,5), Vertex(10,6,5), ColorDbl(0.5, 0.3, 0.5))
    myScene.addTetrahedron(Vertex(8.0, 0, 0), Vertex(8, -4, -4.0), Vertex(10, 0, -4.0), Vertex(8, 4, -4.0), ColorDbl(1.0, 0.0, 0.0));
	Camera myCamera(&myScene);
    //Camera myCamera(&myScene, Vertex(-2.0, 0.0, 0.0), Vertex(-1.0, 0.0, 0.0), 800, 800);

	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}
