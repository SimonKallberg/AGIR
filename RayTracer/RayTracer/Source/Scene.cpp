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
    
    //Wall 4 - orange
    scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), ColorDbl(1.0, 1.0, 0.0)));
    scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(0, -6, 5), ColorDbl(1.0, 1.0, 0.0)));

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

    std::cout << "Added a tetrahedron to the scene!" << std::endl << std::endl;
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
        arg.intSectPoint = &arg.intSectPoints[0].interSectPoint;
        
        if(arg.intSectPoints[0].tri != nullptr ) {
            arg.endTri = arg.intSectPoints[0].tri;
        }
        else {
            arg.endSphere = arg.intSectPoints[0].sphere;
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

//Whitted ray-tracing & monte carlo
void Scene::traceRay(Ray* arg, int iteration) {
    //cout << "iteration: " << iteration << endl;
    //Check for when rays go inbetween triangles
    if(arg == nullptr || arg->start == nullptr || arg->end == nullptr) {
        cout << "null" << endl;
        return;
    }
    
    //Add intersections to ray
    findIntersection(*arg);
    
    if(iteration > 0) {
        return;
    }
    
    if(arg->intSectPoint == nullptr) {
        //cout << "nullptr" << endl;
        return;
    }
    
    //If the ray hits a diffuse triangle
    if(arg->endTri && arg->endTri->surf.reflectionType == 0) {
        arg->monteCarloRay = traceRayMonteCarlo(arg);
        traceRay(arg->monteCarloRay, iteration +1);

    }
    //If the ray hits a diffuse sphere
    else if(arg->endSphere && arg->endSphere->surf.reflectionType == 0) {

        arg->monteCarloRay = traceRayMonteCarlo(arg);
        traceRay(arg->monteCarloRay, iteration +1);
    }
    //Perfect reflection
    else {
        Vector3 normal;
        //Get normal
        if(arg->endTri) {
            normal = arg->endTri->calcNormal();
        }
        else if(arg->endSphere) {
            normal = arg->endSphere->calcNormal(*arg);
        }
        else {
            return;
        }
            
        //Perfectly reflected ray
        Vector3 dir = calcPerfectReflection(*arg, normal);
        Vertex* endVertex = new Vertex(*arg->intSectPoint + dir);
        arg->reflectedRay = new Ray(arg->intSectPoint, endVertex);
        
        //Recurse
        traceRay(arg->reflectedRay, iteration + 1);
    }
}

Ray* Scene::traceRayMonteCarlo(Ray *arg) {

    //Setting up the estimator by generating 2 random numbers [0,1]
    double randX = (*dis)(*gen);
    double randY = (*dis)(*gen);
    double PI = 3.14;
    
    //Monte Carlo solution with a cosine estimator
    double azimuth = 2*PI*randX;
    double inclination = asin(sqrt(randY));

    Vector3 I = (*arg->end - *arg->start).vec3.normalize();
    Vector3 z1 = (arg->endTri ? arg->endTri->normal : arg->endSphere->calcNormal(*arg)).normalize();
    Vector3 x1 = (I - dotProduct(I, z1) * z1).normalize();
    
    //Transform to local coordinate system
    glm::vec3 z((float)z1.x, (float)z1.y, (float)z1.z);
    glm::vec3 x((float)x1.x, (float)x1.y, (float)x1.z);
    glm::vec3 y = glm::normalize(glm::cross(z, -x));
    glm::vec3 random_direction = z;
    
    //Rotate in random direction
    random_direction = glm::normalize(glm::rotate(random_direction, (float) inclination, y));
    random_direction = glm::normalize(glm::rotate(random_direction, (float) azimuth, z));
    
    //Create outgoing direction
    Vector3 outDirGlobal = Vector3((double)random_direction.x, (double)random_direction.y, (double)random_direction.z );
    
    //Add new ray to the tree
    Vertex* endVertex = new Vertex(arg->intSectPoint->vec3 + outDirGlobal);
    Ray *outRay = new Ray(arg->intSectPoint, endVertex);

    return outRay;
}
