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
			Triangle temp;
            Sphere tempS;
			Ray myRay = calcRay(x, y);
            bool shadow = false;
            theScene->findInterObj(myRay, temp, tempS);
            //If the ray hits a tringle
            if(myRay.endTri) {
                //Shoot shadow ray
                if(myRay.intSectPoint) {
                     shadow = theScene->shootShadowRay(*myRay.intSectPoint);
                     //Is there a shadow? Set to black
                     if(shadow) {
                         plane(x, y).color = ColorDbl(temp.color.r-0.3,temp.color.g-0.3,temp.color.b-0.3);
                     }
                     else {
                         plane(x, y).color = temp.color;
                     }
                }
            }
            //If the ray hits a sphere
            else {
                if(myRay.intSectPoint) {
                     shadow = theScene->shootShadowRay(*myRay.intSectPoint);
                     //Is there a shadow? Set to black
                     if(shadow) {
                         plane(x, y).color = ColorDbl(tempS.color.r-0.3,tempS.color.g-0.3,tempS.color.b-0.3);
                     }
                     else {
                         plane(x, y).color = tempS.color;
                     }
                }
            }


            

//            if(theScene->findInterTetra(myRay, tempTetra) != nullptr) {
//                //Shoot shadow ray if ray hits something
//                if(myRay.intSectPoint != nullptr) {
//                   Vector3 dir = calcPerfectReflection(myRay, myRay.endTri->normal);
//                    Vertex dirVert = *myRay.intSectPoint + dir;
//                    Ray mirroredRay = Ray(myRay.intSectPoint, &dirVert);
//
//                    if (theScene->findInterSphere(mirroredRay, tempS) != nullptr){
//                        plane(x, y).color = tempS.color;
//                    }
//                    else if (theScene->findInterTri(mirroredRay, temp) != nullptr) {
//                        plane(x, y).color = temp.color;
//                    }
//                    else {
//
//                    }
//                }
//
//            }
            
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
