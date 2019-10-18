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
            Ray theRay = calcRay(x,y);

            //Shoot out ray
            theScene->traceRay(&theRay, 0);
            
            //Pointer to loop through the ray
            Ray* endRay = &theRay;
            //Access the leaf of the tree
            while(endRay->monteCarloRay) {
                endRay = endRay->monteCarloRay;
            }
            bool shadow = false;
            //If the ray hits a triangle
            if(endRay->endTri) {
                plane(x, y).color = endRay->endTri->surf.color;
                
                 shadow = theScene->shootShadowRay(*endRay->intSectPoint);
                 //Is there a shadow? Set to black
                 if(shadow) {
                     plane(x, y).color = ColorDbl(0,0,0);
                 }
                //Add shading to objects that are hit by light
                 else {
                     Vector3 rayToLight = (theScene->pointLights[0].pos.vec3 - endRay->intSectPoint->vec3);
                     rayToLight.normalize();
                     double alpha = dotProduct(endRay->endTri->normal, rayToLight);
                     if ( alpha > 0 ) {
                        plane(x, y).color = endRay->endTri->surf.color*alpha;
                     }
                     else {
                         plane(x, y).color = ColorDbl(0,0,0);
                     }
                 }
            }
            
            //If the ray its a sphere
            else if(endRay->endSphere) {
                shadow = theScene->shootShadowRay(*endRay->intSectPoint);
                //Is there a shadow? Set to black
                if(shadow) {
                    plane(x, y).color = ColorDbl(0,0,0);
                }
                else {
                    Vector3 rayToLight = (theScene->pointLights[0].pos.vec3 - endRay->intSectPoint->vec3);
                    rayToLight.normalize();
                    double alpha = dotProduct(endRay->endSphere->calcNormal(*endRay), rayToLight);
                    if ( alpha > 0 ) {
                       plane(x, y).color = endRay->endSphere->surf.color*alpha;
                    }
                    else {
                        plane(x, y).color = ColorDbl(0,0,0);
                    }
                }
            }
            else
            {
                plane(x, y).color = ColorDbl(1,0,0);
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
