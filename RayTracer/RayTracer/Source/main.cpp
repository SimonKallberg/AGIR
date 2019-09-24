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


int main()
{
	Scene myScene;
	myScene.initialize();
	Camera myCamera(&myScene);

	myCamera.render();
	myCamera.createImage();

	return 0;
}