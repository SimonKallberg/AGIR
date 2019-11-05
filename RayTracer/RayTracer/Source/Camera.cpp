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
    
    //Make ray shoot from middle of pixel
    double startWidth = deltaWidth/2;
    double startHeight = deltaHeight/2;

	Vertex localCoord = Vertex(0.0, ((double)x*deltaWidth)+startWidth , ((double)y*deltaHeight)+startHeight);
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
            //Calculate ray from eye through the pixel
            Ray theRay = calcRay(x,y);

            //Shoot out 4 rays per ray to implement anti aliasing
            ColorDbl colorOfPixel;
            for(int i = 0; i < 3; i++) {
                colorOfPixel = colorOfPixel + theScene->traceRay(&theRay, 0);
            }
            //Take average of the 4 rays and write to pixel plane
            plane(x, y) = 0.25 * colorOfPixel;
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
