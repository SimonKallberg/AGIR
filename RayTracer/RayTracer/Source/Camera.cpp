//
//  Camera.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Camera.hpp"

Ray Camera::calcRay(int x, int y, float deltaWidth_, float deltaHeight_) {
	float deltaWidth = (float)abs((c1.y - c3.y)) / (float)CAMERA_WIDTH;
	float deltaHeight = -(float)abs((c1.z - c3.z)) / (float)CAMERA_HEIGHT;
    
    //Make ray shoot from middle of pixel
    float startWidth = deltaWidth/2;
    float startHeight = deltaHeight/2;
    
    //Move ray from middle to random place
    startWidth += deltaWidth_;
    startHeight += deltaHeight_;

	vec3 localCoord = vec3(0.0f, ((float)x*deltaWidth)+startWidth , ((float)y*deltaHeight)+startHeight);

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
            int samplesPerPixel = 4;
            //Supersampling & anti-aliasing
            float widthOfCameraPlane = length(c1-c2);
            float heigthOfCameraPlane = length(c3-c4);
            float widthOfPixel = widthOfCameraPlane/(float)CAMERA_WIDTH;
            float heightOfPixel = heigthOfCameraPlane/(float)CAMERA_HEIGHT;
            
            //Get step distance for each pixel sample
            float deltaWidth = widthOfPixel/2.0f;
            float deltaHeight = heightOfPixel/2.0f;
            
            if(x == CAMERA_WIDTH/4 && y == CAMERA_HEIGHT/4) {
                cout << "25% done..." << endl;
            }
            else if(x == CAMERA_WIDTH/2 && y == CAMERA_HEIGHT/2) {
                cout << "50% done..." << endl;
            }
            else if(x == CAMERA_WIDTH*3/4 && y == CAMERA_HEIGHT*3/4) {
                cout << "75% done..." << endl;
            }

            //Shoot out 4 rays per ray to implement supersampling
            vec3 colorOfPixel = vec3(0.0f,0.0f,0.0f);
            for(int i = 0; i < samplesPerPixel; i++) {
                
                //Anti-aliasing - move ray randomly
                uniform_real_distribution<float> randStepSizeWidth(-deltaWidth, deltaWidth);
                uniform_real_distribution<float> randStepSizeHeight(-deltaHeight, deltaHeight);
                
                float randHeight = randStepSizeWidth(*theScene->gen);
                float randWidth = randStepSizeWidth(*theScene->gen);
                
                //Calculate ray from eye through the pixel
                Ray theRay = calcRay(x,y, randHeight, randWidth);
                colorOfPixel = colorOfPixel + theScene->traceRay(&theRay, 0);
            }
            //Take average of the 4 rays and write to pixel plane
            plane(x, y).color = colorOfPixel/(float)samplesPerPixel;
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
