//
//  Camera.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Camera.hpp"

Ray Camera::calcRay(int x, int y) {
	double deltaWidth = (double)abs((c1.vec3.y - c3.vec3.y)) / (double)CAMERA_WIDTH;
	double deltaHeight = -(double)abs((c1.vec3.z - c3.vec3.z)) / (double)CAMERA_HEIGHT;

	Vertex localCoord = Vertex(0.0, (double)x*deltaWidth, (double)y*deltaHeight);
    //TODO resolve memory leak
	Vertex *end = new Vertex(c4 + localCoord);
    Ray theRay = Ray(getActiveEye(), end);
    
	return theRay;
}


void Camera::render()
{
    cout << "Rendering image..." << endl;
	for (int x = 0; x < CAMERA_WIDTH; x++)
	{
		for (int y = 0; y < CAMERA_HEIGHT; y++)
		{
			Triangle temp(Vertex(1.0, 1.0, 0.0), Vertex(1.0, -1.0, 0.0), Vertex(-1.0, -1.0, 0.0));
            Sphere tempS(Vertex(1.0, 1.0, 0.0), 1.0, ColorDbl(1.0, 1.0, 1.0));
			Ray myRay = calcRay(x, y);
			theScene->findInterTri(myRay, temp);
            if(theScene->findInterSphere(myRay, tempS) != nullptr) {
                plane(x, y).color = tempS.color;
            }
            else {
                plane(x, y).color = temp.color;
            }
		}
	}
}

void Camera::createImage(std::string fileName)
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
    image.save_image(fileName);
}

Vertex* Camera::getActiveEye() {
    if(activeEye == RIGHT) {
        return &eyeR;
    }
    else {
        return &eyeL;
    }
}
