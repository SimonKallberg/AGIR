//
//  Scene.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Scene.hpp"



void Scene::initialize()
{
    std::cout << "Setting up triangles...." << std::endl;
    
    //Setting up a room shaped as a polygon
    
    //Wall2 - purple
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(10,6,5), Vertex(0,6,-5), ColorDbl(1.0, 0.0, 1.0)));
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(10,6,-5), Vertex(0,6,-5), ColorDbl(1.0, 0.0, 1.0)));
	
    //Wall 3 - turqoise
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(13,0,5), Vertex(10,6,-5), ColorDbl(0.0, 1.0, 1.0)));
    scene.push_back(Triangle(Vertex(13,0,5), Vertex(13,0,-5), Vertex(10,6,-5), ColorDbl(0.0, 1.0, 1.0)));
    
    //Wall 4 - red
    scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), ColorDbl(1.0, 0.0, 0.0)));
    scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(0, -6, 5), ColorDbl(1.0, 0.0, 0.0)));

	//Wall 5 - blue
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,5), Vertex(0,-6,5), ColorDbl(0.0, 0.0, 1.0)));
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,-5), Vertex(10,-6,5), ColorDbl(0.0, 0.0, 1.0)));
	
    //Wall 6 - green
    scene.push_back(Triangle(Vertex(10,-6,-5), Vertex(13,0,5), Vertex(10,-6,5), ColorDbl(0.0, 1.0, 0.0)));
    scene.push_back(Triangle(Vertex(10,-6,-5), Vertex(13,0,-5), Vertex(13,0,5), ColorDbl(0.0, 1.0, 0.0)));
    
    //celing - white
    scene.push_back(Triangle(Vertex(0, -6, 5), Vertex(0,6,5), Vertex(-3, 0, 5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,6,5), Vertex(0,6,5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(0, -6, 5), Vertex(10,-6,5), Vertex(10, 6, 5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,6,5), ColorDbl(1, 1, 1)));
    
    //floor - white
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(0,6,-5), Vertex(10,6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(10,-6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5), ColorDbl(1, 1, 1)));
    
    // Wall 1 - yellow
       scene.push_back(Triangle(Vertex(-3, 0, 5), Vertex(0, 6, 5), Vertex(-3, 0, -5), ColorDbl(1.0, 1.0, 0.0)));
       scene.push_back(Triangle(Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(-3, 0, -5), ColorDbl(1.0, 1.0, 0.0)));
}



void Scene::addTetrahedron(Vertex inV, double scale, ColorDbl incolor, int reflType) {
	
    //Closest to camera
	Vertex corner1 = inV + scale*Vertex(-sqrt(8.0/9.0), 0, -(1.0/3.0));
    //Right back
	Vertex corner2 = inV + scale*Vertex(sqrt(2.0 / 9.0), sqrt(2.0 / 3.0), -(1.0/3.0));
    //Left back
	Vertex corner3 = inV + scale*Vertex(sqrt(2.0 / 9.0), -1* sqrt(2.0 / 3.0), -(1.0/3.0));
    Vertex top = inV.vec3 + scale*Vertex(0.0, 0.0, 1.0);

    //Adding triangles to scene
    //Back
    scene.push_back(Triangle(top, corner2, corner3, incolor, reflType));
    //Bottom
    scene.push_back(Triangle(corner1, corner3, corner2, incolor, reflType));
    //Front right
    scene.push_back(Triangle(top, corner1, corner2, incolor, reflType));
    //Front left
    scene.push_back(Triangle(top, corner3, corner1,  incolor, reflType));

    std::cout << "Added a tetrahedron to the scene!" << std::endl;
}

void Scene::addSphere(Vertex inCenter, double radius, ColorDbl inColor, int inReflType) {
    spheres.push_back(Sphere(inCenter, radius, inColor, inReflType));
    
    std::cout << "Added a sphere with center: " << inCenter << "color: " << inColor << "radius: " << radius << " to the scene!" << std::endl << std::endl;
}

Vertex* Scene::findIntersection(Ray &arg) {
        
    for(int i = 0; i < (int)scene.size(); i++) {
        scene[i].rayIntersection(arg);
    }
    
    for(int i = 0; i < (int)spheres.size(); i++) {
        spheres[i].rayIntersection(arg);
    }
    
    if(arg.intSectPoints.size() > 0) {
        arg.sortIntersections();
        //Check if start point is the same as end point
        arg.intSectPoint = &arg.intSectPoints[0].interSectPoint;
        int i = 0;
//        if( (arg.start->vec3 - arg.intSectPoint->vec3).length() < 0.00001 ) {
//            cout << "Intersection point same as starting point" << endl;
//            if((int)arg.intSectPoints.size() > 1) {
//                cout << "Changing intersection point" << endl;
//                i = 1;
//            }
//        }
        arg.intSectPoint = &arg.intSectPoints[i].interSectPoint;
        
        if(arg.intSectPoints[i].tri != nullptr ) {
            arg.endTri = arg.intSectPoints[i].tri;
            arg.refractionIndex = arg.endTri->refractionIndex;
        }
        else {
            arg.endSphere = arg.intSectPoints[i].sphere;
            arg.refractionIndex = arg.endSphere->refractionIndex;
        }
        
    return arg.intSectPoint;
        
    }
    return nullptr;
}

void Scene::addPointLight(Vertex inCenter) {
    pointLights.push_back(PointLight(inCenter));
    
    std::cout << "Added a pointlight with center: " << inCenter << "to the scene!" << std::endl << std::endl;
}

bool Scene::shootShadowRay(Vertex &inV) {
    
    for(int i = 0; i < (int)pointLights.size(); i++) {
        Ray theRay = Ray(&inV, &pointLights[i].pos);
        
        //Check if an object is intersecting ray to light
        if(findIntersection(theRay) != nullptr) {
            //Check so distance to light is greater than distance to intersecting object
            double distToLight = (theRay.end->vec3 - theRay.start->vec3).length();
            double distToIntersection = (theRay.intSectPoint->vec3 - theRay.start->vec3).length();
            
            if( distToIntersection < distToLight ){
                return true;
            }
        }
    }
    return false;
}

//Whitted ray-tracing
void Scene::rayTracing(Ray* arg, int iteration) {
    
    if(iteration > 10) {
        //cout << "breaking" << endl;
        return;
    }
    
    //Check for when rays go inbetween triangles
    if(arg == nullptr || arg->start == nullptr || arg->end == nullptr) {
        //cout << "break 1" << endl;
        return;
    }
    //Add intersections to ray
    findIntersection(*arg);
    
    if(arg->intSectPoint == nullptr) {
        //cout << "break 2" << endl;
        return;
    }
    
    //If the ray hits a diffuse triangle, stop the recursion!
    if(arg->endTri && arg->endTri->surf.reflectionType == 0) {
        //cout << "break 4" << endl;
        return;
    }
    //If the ray hits a diffuse sphere, stop the recursion!
    else if(arg->endSphere && arg->endSphere->surf.reflectionType == 0) {
        //cout << "break 5" << endl;
        return;
    }
    else {
        //Get normal and refraction index
        Vector3 normal;
        if(arg->endTri) {
            normal = arg->endTri->calcNormal();
        }
        else if(arg->endSphere) {
            normal = arg->endSphere->calcNormal(*arg);
            //cout << "Sphere: n2" << n2 << endl;
        }
        else {
            //cout << "break 6" << endl;
            return;
        }
        
        //Perfectly reflected ray
        Vector3 dir = calcPerfectReflection(*arg, normal);
        Vertex* endVertex = new Vertex(*arg->intSectPoint + dir);
        arg->reflectedRay = new Ray(arg->intSectPoint, endVertex);
        arg->reflectedRay->parent = arg;
        
        //Perfectly refracted ray
//        bool inside = false;
//        double n1 = 1;
//        double n2 = arg->refractionIndex;
//        if(arg->parent != nullptr) {
//            n1 = arg->parent->refractionIndex;
//        }
//
//        Vector3 dirRefr = calcRefraction(*arg, normal, n1, n2);
//        //No refraction exists!
//        if( dirRefr < 0.1) {
//            return;
//        }
        
//        Vertex* newStartPoint = new Vertex(*arg->intSectPoint + (normal*0.01));
//        Vertex* endRefrVertex = new Vertex(*arg->intSectPoint + dirRefr);
//        arg->refractedRay = new Ray(newStartPoint, endRefrVertex);
//        arg->refractedRay->parent = arg;
        //cout << *arg->refractedRay->parent << endl;
        //cout << *arg->intSectPoint << endl;
        //cout << *arg->refractedRay << endl;
            
        //Recurse refraction
        //rayTracing(arg->refractedRay, iteration + 1);
        
        //Recurse reflection
        rayTracing(arg->reflectedRay, iteration + 1);
    }
}

