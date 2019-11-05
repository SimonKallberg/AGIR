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
    
    //Wall2 - matte light pink
    scene.push_back(Triangle(Vertex(0,6,5),Vertex(10,6,5), Vertex(0,6,-5), ColorDbl(0.94, 0.66, 0.73)));
    scene.push_back(Triangle(Vertex(10,6,5),Vertex(10,6,-5),Vertex(0,6,-5),ColorDbl(0.94, 0.66, 0.73)));
	
    //Wall 3 - matte blue
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(13,0,5), Vertex(10,6,-5), ColorDbl(0.36, 0.45, 0.63)));
    scene.push_back(Triangle(Vertex(13,0,5), Vertex(13,0,-5), Vertex(10,6,-5), ColorDbl(0.36, 0.45, 0.63)));
    
    //Wall 4 - dark matte pink
    scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, 5), Vertex(-3, 0, 5), ColorDbl(0.76, 0.4, 0.5)));
    scene.push_back(Triangle(Vertex(-3, 0, -5), Vertex(0, -6, -5), Vertex(0, -6, 5), ColorDbl(0.76, 0.4, 0.5)));

	//Wall 5 - dark green
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,5), Vertex(0,-6,5), ColorDbl(0.23, 0.31, 0.27)));
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,-5), Vertex(10,-6,5), ColorDbl(0.23, 0.31, 0.27)));
	
    //Wall 6 - green
    scene.push_back(Triangle(Vertex(10,-6,-5), Vertex(13,0,5), Vertex(10,-6,5), ColorDbl(0.92, 0.64, 0.59)));
    scene.push_back(Triangle(Vertex(10,-6,-5), Vertex(13,0,-5), Vertex(13,0,5), ColorDbl(0.92, 0.64, 0.59)));
    
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
ColorDbl Scene::traceRay(Ray* arg, int iteration) {

    //Check for when rays go inbetween triangles
    if(arg == nullptr || arg->start == nullptr || arg->end == nullptr) {
        return ColorDbl();
    }
    
    //Add intersections to ray
    findIntersection(*arg);
    
    if(arg->intSectPoint == nullptr) {
        return ColorDbl();
    }
    
    ColorDbl diffuse = 0.5 * getLambertianSurfaceColor(*arg);
    
    if( iteration > 1) {
        return diffuse;
    }
    
    //Diffuse surface, monte carlo ray tracing
    if((arg->endTri && arg->endTri->surf.reflectionType == 0) ||
      (arg->endSphere && arg->endSphere->surf.reflectionType == 0)) {
        //Monte carlo ray
        arg->monteCarloRay = traceRayMonteCarlo(arg);
        //Recurse
        diffuse = diffuse + 0.7 * traceRay(arg->monteCarloRay, iteration + 1);
    }
    //Perfectly reflective surface
    else if((arg->endSphere && arg->endSphere->surf.reflectionType == 1) ||
            (arg->endTri && arg->endTri->surf.reflectionType == 1)) {
        
        //Perfectly reflected ray
        arg->reflectedRay = traceRayPerfectReflection(*arg);
        //Recurse
        diffuse = traceRay(arg->reflectedRay, iteration + 1);
    }
    return diffuse;
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

Ray* Scene::traceRayPerfectReflection(Ray &inRay) {
    Vector3 I = (*inRay.end - *inRay.start).vec3.normalize();
    Vector3 normal = (inRay.endTri ? (inRay.endTri->normal) : (inRay.endSphere->calcNormal(inRay))).normalize();
    Vector3 outDir = (I - 2*(dotProduct(I,normal)*normal));
    Ray* outRay = new Ray(inRay.intSectPoint, new Vertex(inRay.intSectPoint->vec3 + outDir));
    
    return outRay;
}

ColorDbl Scene::getLambertianSurfaceColor(Ray &endRay) {
    bool shadow = false;
        //If the ray hits a triangle
        if(endRay.endTri) {
            
             shadow = shootShadowRay(*endRay.intSectPoint);
             //Is there a shadow? Set to black
             if(shadow) {
                 return ColorDbl(0,0,0);
             }
            //Add shading to objects that are hit by light
             else {
                 Vector3 rayToLight = (pointLights[0].pos.vec3 - endRay.intSectPoint->vec3);
                 rayToLight.normalize();
                 double alpha = dotProduct(endRay.endTri->normal, rayToLight);
                 if ( alpha > 0 ) {
                    return endRay.endTri->surf.color*alpha;
                 }
                 else {
                     return ColorDbl(0,0,0);
                 }
             }
        }
        
        //If the ray its a sphere
        else if(endRay.endSphere) {
            shadow = shootShadowRay(*endRay.intSectPoint);
            //Is there a shadow? Set to black
            if(shadow) {
                return ColorDbl(0,0,0);
            }
            else {
                Vector3 rayToLight = (pointLights[0].pos.vec3 - endRay.intSectPoint->vec3);
                rayToLight.normalize();
                double alpha = dotProduct(endRay.endSphere->calcNormal(endRay), rayToLight);
                if ( alpha > 0 ) {
                   return endRay.endSphere->surf.color*alpha;
                }
                else {
                    return ColorDbl(0,0,0);
                }
            }
        }
        else
        {
            return ColorDbl(1,0,0);
        }
}

