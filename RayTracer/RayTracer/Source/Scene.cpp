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
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(13,0,5), Vertex(10,6,-5), ColorDbl(0.0, 9.0, 1.0)));
    scene.push_back(Triangle(Vertex(13,0,5), Vertex(13,0,-5), Vertex(10,6,-5), ColorDbl(0.0, 1.0, 1.0)));

	//Wall 5 - blue
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,5), Vertex(0,-6,5), ColorDbl(0.0, 0.0, 7.0)));
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,-5), Vertex(10,-6,5), ColorDbl(0.0, 0.0, 1.0)));
	
    //Wall 6 - green
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,-6,-5), ColorDbl(0.0, 8.0, 0.0)));
    scene.push_back(Triangle(Vertex(10,-6,-5), Vertex(13,0,-5), Vertex(13,0,5), ColorDbl(0.0, 1.0, 0.0)));
    
    //Floor - white
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(0,6,5), Vertex(-3,0,5), ColorDbl(1, 1, 0.9)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,6,5), Vertex(0,6,5), ColorDbl(0.9, 0.9, 1)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,-6,5), Vertex(10,6,5), ColorDbl(0.9, 1, 1)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,6,5), ColorDbl(1, 0.9, 1)));
    
    //Ceiling - white
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 0.9)));
    scene.push_back(Triangle(Vertex(0,6,-5), Vertex(10,6,-5), Vertex(0,-6,-5), ColorDbl(1, 0.9, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(10,-6,-5), Vertex(0,-6,-5), ColorDbl(0.9, 1, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5), ColorDbl(0.9, 0.9, 1)));

	// Wall 1 - yellow
	scene.push_back(Triangle(Vertex(-3, 0, 5), Vertex(0, 6, 5), Vertex(-3, 0, -5), ColorDbl(1.0, 1.0, 0.0)));
	scene.push_back(Triangle(Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(-3, 0, -5), ColorDbl(1.0, 1.0, 0.0)));

	//Wall 4 - red
	scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), ColorDbl(1.0, 0.0, 0.0)));
	scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(0, -6, 5), ColorDbl(1.0, 0.0, 0.0)));
}

Vertex* Scene::findInterTri(Ray &arg, Triangle &t1)
{

    for(int i = 0; i < scene.size(); i++) {
        if(scene[i].rayIntersection(arg)) {
            t1 = scene[i];
            return arg.intSectPoint;
        }
    }
    return nullptr;
}

Vertex* Scene::findInterTetra(Ray &arg, Triangle &t1)
{
    Vertex* result = nullptr;
    for(int i = 0; i < tetrahedra.size(); i++) {
        if(tetrahedra[i].rayIntersection(arg)) {
            if(result != nullptr ) {
                if( (*arg.intSectPoint - *arg.start).vec3.length() < ((*result-*arg.start).vec3.length()) ) {
                    t1 = tetrahedra[i];
                    result = arg.intSectPoint;
                }
            }
        }
    }
    return result;
}

void Scene::addTetrahedron(Vertex top, Vertex corner1, Vertex corner2, Vertex corner3, ColorDbl incolor) {
    //Sides
    tetrahedra.push_back(Triangle(top, corner1, corner2, incolor));
    tetrahedra.push_back(Triangle(top, corner2, corner3, incolor));
    tetrahedra.push_back(Triangle(top, corner1, corner3, incolor));
    //Bottom
    tetrahedra.push_back(Triangle(corner1, corner2, corner3, incolor));
    std::cout << "Added a tetrahedron to the scene!" << std::endl;
}

void Scene::addSphere(Vertex inCenter, double radius, ColorDbl inColor) {
    spheres.push_back(Sphere(inCenter, radius, inColor));
    
    std::cout << "Added a sphere with center: " << inCenter << "color: " << inColor << "radius: " << radius << " to the scene!" << std::endl << std::endl;
}

Vertex* Scene::findInterSphere(Ray &arg, Sphere &s1)
{
    for(int i = 0; i < (int)spheres.size(); i++) {
        if(spheres[i].rayIntersection(arg)) {
            s1 = spheres[i];
            return arg.intSectPoint;
        }
    }
    arg.intSectPoint = nullptr;
    return nullptr;
}

void Scene::addPointLight(Vertex inCenter) {
    pointLights.push_back(PointLight(inCenter));
    
    std::cout << "Added a pointlight with center: " << inCenter << "to the scene!" << std::endl << std::endl;
}

bool Scene::shootShadowRay(Vertex &inV) {
    Ray theRay = Ray(&inV, &pointLights[0].pos);
    Triangle tempT;
    Sphere tempS;
    //If a sphere is in between point and light source, return color
    if(findInterSphere(theRay, tempS) != nullptr) {
        return true;
    }
    //If a triangle is in between point and light source, return color
    if(findInterTetra(theRay, tempT) != nullptr) {
        //Margin - checks that point of intersection isn't same as start point
        if((theRay.intSectPoint->vec3 - theRay.start->vec3).length() < 0.01) {
            return false;
        }
       return true;
    }
    return false;
}
