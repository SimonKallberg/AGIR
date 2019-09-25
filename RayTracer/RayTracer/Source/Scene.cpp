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
    // Wall 1 - yellow
    scene.push_back(Triangle(Vertex(-3,0,5), Vertex(0,6,5), Vertex(-3,0,-5), ColorDbl(1.0, 1.0,0.0)));
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(0,6,-5), Vertex(-3,0,-5), ColorDbl(1.0, 1.0, 0.0)));
    
    //Wall 4 - red
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,5), Vertex(-3,0,5), ColorDbl(1.0, 0.0, 0.0)));
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,-5), Vertex(0,-6,5), ColorDbl(1.0, 0.0, 0.0)));
    
    //Wall2 - purple
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(10,6,5), Vertex(0,6,-5), ColorDbl(9.0, 0.0, 9.0)));
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
    
    //Floor - grey
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(0,6,5), Vertex(-3,0,5), ColorDbl(0.5, 0.4, 0.5)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,6,5), Vertex(0,6,5), ColorDbl(0.5, 0.5, 0.4)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,-6,5), Vertex(10,6,5), ColorDbl(0.6, 0.5, 0.5)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,6,5), ColorDbl(0.5, 0.3, 0.5)));
    
    //Ceiling - white
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,6,-5), Vertex(0,-6,-5), ColorDbl(1, 1, 0.9)));
    scene.push_back(Triangle(Vertex(0,6,-5), Vertex(10,6,-5), Vertex(0,-6,-5), ColorDbl(1, 0.9, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(10,-6,-5), Vertex(0,-6,-5), ColorDbl(0.9, 1, 1)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5), ColorDbl(0.9, 0.9, 1)));
}

Vertex* Scene::findInterTri(Ray &arg, Triangle &t1)
{
    for(int i = 0; i < scene.size(); i++) {
        //std::cout << i << std::endl;
        if(scene[i].rayIntersection(arg)) {
            std::cout << i << std::endl;
            t1 = scene[i];
            //std::cout << scene[i].color << std::endl;
            //std::cout << t1.color << std::endl;
            return arg.intSectPoint;
        }
    }
    return nullptr;
}
