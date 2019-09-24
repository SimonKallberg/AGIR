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
    // Wall 1
    scene.push_back(Triangle(Vertex(-3,0,5), Vertex(0,6,5), Vertex(-3,0,-5), ColorDbl(0.7,0.8,0.9)));
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(0,6,-5), Vertex(-3,0,-5), ColorDbl(0.7, 0.9, 0.9)));
	//Wall2
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(10,6,5), Vertex(0,6,-5), ColorDbl(0.6, 0.5, 0.3)));
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(10,6,-5), Vertex(0,6,-5), ColorDbl(0.6, 0.5, 0.3)));
	//Wall 3
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(13,0,5), Vertex(10,6,-5), ColorDbl(0.9, 0.3, 0.7)));
    scene.push_back(Triangle(Vertex(13,0,5), Vertex(13,0,-5), Vertex(10,6,-5), ColorDbl(0.9, 0.3, 0.7)));
    //Wall 4
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,5), Vertex(-3,0,5), ColorDbl(0.4, 0.8, 0.3)));
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,-5), Vertex(0,-6,5), ColorDbl(0.4, 0.0, 0.3)));
	//Wall 5
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,5), Vertex(0,-6,5), ColorDbl(0.2, 0.1, 0.3)));
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,-5), Vertex(10,-6,5), ColorDbl(0.2, 0.1, 0.3)));
	//Wall 6
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,-6,-5), ColorDbl(0.4, 0.3, 0.8)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,-5), Vertex(13,0,5), ColorDbl(0.4, 0.3, 0.8)));
    
    //Toppen
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(0,6,5), Vertex(-3,0,5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,6,5), Vertex(0,6,5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,-6,5), Vertex(10,6,5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,6,5), ColorDbl(1, 1, 1)));
    
    //Botten
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(0,6,-5), Vertex(10,6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(10,-6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5), ColorDbl(1, 1, 1)));
    
}

Vertex* Scene::findInterTri(Ray arg, Triangle &t1)
{
    for(int i = 0; i < scene.size(); i++) {
        if(scene[i].rayIntersection(arg)) {
            t1 = scene[i];
            return arg.intSectPoint;
        }
    }
    return nullptr;
}
