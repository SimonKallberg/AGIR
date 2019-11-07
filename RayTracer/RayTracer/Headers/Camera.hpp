//
//  Camera.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Camera_hpp
#define Camera_hpp


#include <stdio.h>
#include "vec3.hpp"
#include "Pixel.hpp"
#include <iostream>
#include "bitmap_image.hpp"
#include "matrix.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Scene.hpp"
#include "Surface.hpp"
#include "glm.hpp"

using namespace glm;
using namespace std;


class Camera {
public:
    bool RIGHT = true;
    bool LEFT = false;
	vec3 eyeL, eyeR;
	Scene* theScene = nullptr;
	bool activeEye = LEFT; // if false, left eye. If true, right eye
	Camera(Scene* inScene, vec3 inL = vec3(-1.0f, 0.0f, 0.0f), vec3 inR = vec3(-2.0f, 0.0f, 0.0f),
           int camWidth = 800, int camHeigth = 800)
		: theScene(inScene), eyeL(inL), eyeR(inR), plane(camWidth, camHeigth), CAMERA_WIDTH(camWidth),
        CAMERA_HEIGHT(camHeigth) {}

	vec3 c1 = vec3(0.0f, -1.0f, -1.0f);
	vec3 c2 = vec3(0.0f, 1.0f, -1.0f);
	vec3 c3 = vec3(0.0f, 1.0f, 1.0f);
	vec3 c4 = vec3(0.0f, -1.0f, 1.0f);

    int CAMERA_WIDTH;
    int CAMERA_HEIGHT;

	matrix<Pixel> plane;

	Ray calcRay(int x, int y);
	void render();
	void createImage(std::string fileName);
    vec3* getActiveEye();
};

#endif
