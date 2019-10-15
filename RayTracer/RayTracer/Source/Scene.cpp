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
void Scene::rayTracing(Ray* arg, int iteration) {
    
    //Check for when rays go inbetween triangles
    if(arg == nullptr || arg->start == nullptr || arg->end == nullptr) {
        return;
    }
    if(iteration > 5) return;
    
    //Add intersections to ray
    findIntersection(*arg);
    
    if(arg->intSectPoint == nullptr) {
        return;
    }
    
    if( (arg->start->vec3 - arg->intSectPoint->vec3) < 0.1 ||
       -1*(arg->start->vec3 - arg->intSectPoint->vec3) > 0.1 ) {
        return;
    }
    
    Vector3 normal;
    
    //If the ray hits a diffuse triangle, stop the recursion!
    if(arg->endTri && arg->endTri->surf.reflectionType == 0) {
        arg->monteCarloRay = monteCarloRayTracing(*arg);
        rayTracing(arg->monteCarloRay, iteration +1);
    }
    //If the ray hits a diffuse sphere, stop the recursion!
    else if(arg->endSphere && arg->endSphere->surf.reflectionType == 0) {
        arg->monteCarloRay = monteCarloRayTracing(*arg);
        rayTracing(arg->monteCarloRay, iteration +1);
    }
    else {
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
        rayTracing(arg->reflectedRay, iteration + 1);
    }
}

matrix<double> Scene::transformToLocalCoordinateSystem(Ray &arg) {

    Vector3 I = (*arg.end - *arg.start).vec3;
    Vector3 z = arg.endTri ? arg.endTri->normal : arg.endSphere ? arg.endSphere->calcNormal(arg) : Vector3(0,0,0);
    z.normalize();
    Vector3 x = I - dotProduct(I, z) * z;
    x.normalize();
    Vector3 y = crossProduct(-1*x, z);
    y.normalize();
    matrix<double> transform(4,4);
    
    if(arg.intSectPoint) {
        matrix<double> translation(x, y, z);
        Vector3 col1 = Vector3(1, 0, 0);
        Vector3 col2 = Vector3(0, 1, 0);
        Vector3 col3 = Vector3(0, 0, 1);
        matrix<double> rotation(col1, col2, col3, -1*(arg.intSectPoint->vec3));
        transform.multiply(translation, rotation);
    }
    
    return transform;
}

Ray* Scene::monteCarloRayTracing(Ray &arg) {
    
    //If the ray doesn't intersect, there can't be a reflected ray
    if(!arg.intSectPoint) return new Ray(nullptr, nullptr);
    //Setting up the estimator by generating 2 random numbers [0,1]
    double randX = ((double) rand() / (RAND_MAX));
    double randY = ((double) rand() / (RAND_MAX));
    double PI = 3.14;
    
    //Monte Carlo solution with a cosine estimator
    double azimuthAngle = 2*PI*randX;
    double inclinationAngle = asin(sqrt(randY));
    
    //Inclination rotation
    Vector3 col1 = Vector3(cos(inclinationAngle), sin(inclinationAngle), 0);
    Vector3 col2 = Vector3(-sin(inclinationAngle), cos(inclinationAngle), 0);
    Vector3 col3 = Vector3(0,0,1);
    matrix<double> inclinationRotation(col1, col2, col3);
    
    //Azimuth rotation
    col1 = Vector3(1, 0, 0);
    col2 = Vector3(0, cos(azimuthAngle), sin(azimuthAngle));
    col3 = Vector3(0, -sin(azimuthAngle), cos(azimuthAngle));
    matrix<double> azimuthRotation(col1, col2, col3);
    
    //Total rotation
    matrix<double> rotation(4,4);
    rotation.multiply(azimuthRotation, inclinationRotation);
    
    //Getting outgoing direction by transforming to local coordinate system
    matrix<double> changeCoords = transformToLocalCoordinateSystem(arg);
    Vector3 inDir = (*arg.end - *arg.start).vec3;
    Vector3 inDirLocal = changeCoords.multiply(inDir);
    Vector3 outDirLocal = rotation.multiply(inDirLocal);
    Vector3 outDirGlobal;
    
    //Transform to global coordinate system
    changeCoords.invert();
    outDirGlobal = changeCoords.multiply(outDirLocal);
    Vertex* endVertex = new Vertex(arg.intSectPoint->vec3 + outDirGlobal);
    
    Ray *outRay = new Ray(endVertex, arg.start);
    return outRay;
}
