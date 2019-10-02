//
//  Camera.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Camera_hpp
#define Camera_hpp


#include <stdio.h>
#include "Vertex.hpp"
#include "Pixel.hpp"
#include <iostream>
#include "bitmap_image.hpp"
#include "matrix.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Scene.hpp"
#include "Surface.hpp"


class Camera {
public:
    bool RIGHT = true;
    bool LEFT = false;
	Vertex eyeL, eyeR;
	Scene* theScene = nullptr;
	bool activeEye = LEFT; // if false, left eye. If true, right eye
	Camera(Scene* inScene, Vertex inL = Vertex(-1.0, 0.0, 0.0), Vertex inR = Vertex(-2.0, 0.0, 0.0),
           int camWidth = 800, int camHeigth = 800)
		: theScene(inScene), eyeL(inL), eyeR(inR), plane(camWidth, camHeigth), CAMERA_WIDTH(camWidth),
        CAMERA_HEIGHT(camHeigth) {}

	Vertex c1 = Vertex(0.0, -1.0, -1.0);
	Vertex c2 = Vertex(0.0, 1.0, -1.0);
	Vertex c3 = Vertex(0.0, 1.0, 1.0);
	Vertex c4 = Vertex(0.0, -1.0, 1.0);

    int CAMERA_WIDTH;
    int CAMERA_HEIGHT;

	matrix<Pixel> plane;

	Ray calcRay(int x, int y);
	void render();
	void createImage(std::string fileName);
    Vertex* getActiveEye();
};

#endif
