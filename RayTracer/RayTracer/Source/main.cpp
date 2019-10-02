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
    myScene.addTetrahedron(Vertex(8.0, 0, 2), Vertex(8, -4, -2.0), Vertex(10, 0, 0.0), Vertex(8, 4, -2.0), ColorDbl(1.0, 0.0, 1.0));
    for(int i = 0; i < (int)myScene.tetrahedra.size(); i++) {
        myScene.tetrahedra[i].flipNormal();
    }
    
    
    //Adding a grey sphere
    myScene.addSphere(Vertex(6.0,0.0,-4.0), 2.0, ColorDbl(0.5, 0.5, 0.5));
    myScene.addPointLight(Vertex(8.0,0.0,5.0));
	Camera myCamera(&myScene);


	myCamera.render();
	myCamera.createImage("raytracing.bmp");

	return 0;
}
