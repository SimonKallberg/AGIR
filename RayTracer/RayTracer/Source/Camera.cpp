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
//    int x = 0;
//    int y = 0;
            Ray theRay = calcRay(x,y);
            
            //Find intersection with ray
            theScene->findIntersection(theRay);
            //Shoot out ray
            theScene->rayTracing(&theRay, 0);
            
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
            
            
     
   //OLD THIS WORKS
            //If the ray hits a tringle
//            if(myRay.endTri) {
//                //Shoot shadow ray
//                if(myRay.intSectPoint) {
//                     shadow = theScene->shootShadowRay(*myRay.intSectPoint);
//                     //Is there a shadow? Set to black
//                     if(shadow) {
//                         plane(x, y).color = ColorDbl(0,0,0);
//                     }
//                    //Add shading to objects that are hit by light
//                     else {
//						 Vector3 rayToLight = (theScene->pointLights[0].pos.vec3 - myRay.intSectPoint->vec3);
//						 rayToLight.normalize();
//						 double alpha = dotProduct(myRay.endTri->normal, rayToLight);
//                         if ( alpha > 0 ) {
//                            plane(x, y).color = myRay.endTri->surf.color*alpha;
//                         }
//                         else {
//                             plane(x, y).color = myRay.endTri->surf.color;
//                         }
//                     }
//                }
//            }
//            //If the ray hits a sphere
//            else {
//                if(myRay.intSectPoint) {
//
//                     shadow = theScene->shootShadowRay(*myRay.intSectPoint);
//                     //Is there a shadow? Set to black
//                     if(shadow) {
//                         plane(x, y).color = ColorDbl(0,0,0);
//                     }
//                     else {
//                         Vector3 rayToLight = (theScene->pointLights[0].pos.vec3 - myRay.intSectPoint->vec3);
//                         rayToLight.normalize();
//                         double alpha = dotProduct(myRay.endSphere->calcNormal(myRay), rayToLight);
//                         if ( alpha > 0 ) {
//                            plane(x, y).color = myRay.endSphere->surf.color*alpha;
//                         }
//                         else {
//                             plane(x, y).color = myRay.endSphere->surf.color;
//                         }
//                     }
//                }
//            }
//
            //Perfect refraction
//            if(myRay.endSphere) {
//                //Shoot shadow ray if ray hits something
//                if(myRay.intSectPoint != nullptr) {
//                    Vector3 dir = calcRefraction(myRay, myRay.endSphere->calcNormal(myRay), 0.2, 0.8);
//                    Vertex dirVert = *myRay.intSectPoint + dir;
//                    Ray mirroredRay = Ray(myRay.intSectPoint, &dirVert);
//                    theScene->findIntersection(mirroredRay);
//
//                    if(mirroredRay.intSectPoints.size() >= 2) {
//                        if (mirroredRay.intSectPoints[1].tri != nullptr){
//                            plane(x, y).color = mirroredRay.intSectPoints[1].tri->surf.color;
//                        }
//                        else if (mirroredRay.intSectPoints[1].sphere != nullptr) {
//                            plane(x, y).color = mirroredRay.intSectPoints[1].sphere->surf.color;
//                        }
//                        else {
//
//                        }
//                    }
//                }
//

            //Perfect mirror
//            if(myRay.endSphere) {
//                //Shoot shadow ray if ray hits something
//                if(myRay.intSectPoint != nullptr) {
//                    Vector3 dir = calcPerfectReflection(myRay, myRay.endSphere->calcNormal(myRay));
//                    Vertex dirVert = *myRay.intSectPoint + dir;
//                    Ray mirroredRay = Ray(myRay.intSectPoint, &dirVert);
//                    theScene->findIntersection(mirroredRay);
//
//                    if (mirroredRay.endTri != nullptr){
//                        plane(x, y).color = mirroredRay.endTri->surf.color;
//                    }
//                    else if (mirroredRay.endSphere != nullptr) {
//                        plane(x, y).color = mirroredRay.endSphere->surf.color;
//                    }
//                    else {
//
//                    }
//                }

           // }
            
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
