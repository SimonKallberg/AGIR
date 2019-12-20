//
//  Camera.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Camera.hpp"

Ray Camera::calcRay(int x, int y) {
	float deltaWidth = (float)abs((c1.y - c3.y)) / (float)CAMERA_WIDTH;
	float deltaHeight = -(float)abs((c1.z - c3.z)) / (float)CAMERA_HEIGHT;
    
    //Make ray shoot from middle of pixel
    float startWidth = deltaWidth/2;
    float startHeight = deltaHeight/2;

	vec3 localCoord = vec3(0.0f, ((float)x*deltaWidth)+startWidth , ((float)y*deltaHeight)+startHeight);
    //TODO resolve memory leak
	vec3 *end = new vec3(c4 + localCoord);
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
            
            if( x == 200 && y == 400) {
                cout << "25% done..." << endl;
            }
            else if(x == 400 && y == 400) {
                cout << "50% done..." << endl;
            }
            else if(x == 600 && y == 400) {
                cout << "75% done..." << endl;
            }

            //Shoot out 4 rays per ray to implement anti aliasing
            vec3 colorOfPixel = vec3(0.0f,0.0f,0.0f);
            for(int i = 0; i < 3; i++) {
                colorOfPixel = colorOfPixel + theScene->traceRay(&theRay, 0);
            }
            //Take average of the 4 rays and write to pixel plane
            plane(x, y).color = colorOfPixel * 0.25f;
		}
	}
//    //Debugging
//    Ray theRay = calcRay(200,600);
//    plane(200, 600).color = theScene->traceRay(&theRay, 0);
}

void Camera::createImage(std::string fileName)
{
    bitmap_image image(CAMERA_WIDTH, CAMERA_HEIGHT);
    image.clear();
    
    //Set pixels to the camera plane
    for(int x = 0; x < CAMERA_WIDTH; x++) {
        for(int y = 0; y < CAMERA_HEIGHT; y++) {
            unsigned int r = (int)(plane(x, y).color.x * 255.0f);
            unsigned int g = (int)(plane(x, y).color.y * 255.0f);
            unsigned int b = (int)(plane(x, y).color.z * 255.0f);
            
            rgb_t color = make_colour(r, g, b);
            image.set_pixel( x,  y, color);
        }
    }
    cout << "Saving image..." << endl;
    image.save_image(fileName);
}

vec3* Camera::getActiveEye() {
    if(activeEye == RIGHT) {
        return &eyeR;
    }
    else {
        return &eyeL;
    }
}
