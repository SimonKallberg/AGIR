//
//  Camera.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Camera.hpp"

void Camera::calcRay(int x, int y, Ray &r) {
	double deltaWidth = (double)(c1.y - c3.y) / (double)CAMERA_WIDTH;
	double deltaHeight = (double)(c1.z - c3.z) / (double)CAMERA_HEIGHT;

	Vertex localCoord = Vertex(0.0, (double)x*deltaWidth, (double)y*deltaHeight);
	Vertex end = c1 + localCoord;

	r = Ray(&eyeL, &end);
}


void Camera::render()
{
	for (int x = 0; x < CAMERA_WIDTH; x++)
	{
		for (int y = 0; y < CAMERA_HEIGHT; y++)
		{
			Triangle temp(Vertex(1.0, 1.0, 0.0), Vertex(1.0, -1.0, 0.0), Vertex(-1.0, -1.0, 0.0));
			Ray myRay = Ray(&eyeL,&eyeR);
			calcRay(x, y, myRay);
			theScene->findInterTri(myRay, temp);
			plane(x, y).color = temp.color;
		}
	}
}

void Camera::createImage()
{
    bitmap_image image(CAMERA_WIDTH, CAMERA_HEIGHT);
    image.clear();
    
    //Set pixels to the camera plane
    for(int x = 0; x < CAMERA_WIDTH; x++) {
        for(int y = 0; y < CAMERA_HEIGHT; y++) {
			unsigned int r = (int)(plane(x, y).color.r * 255);
			unsigned int g = (int)(plane(x, y).color.g * 255);
			unsigned int b = (int)(plane(x, y).color.b * 255);
            rgb_t color = make_colour(r, g, b);
            image.set_pixel( x,  y, color);
        }
    }
    cout << "Saving image..." << endl;
    image.save_image("raytracing.bmp");
}
