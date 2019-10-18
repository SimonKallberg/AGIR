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
void Scene::rayTracing(Ray* arg, int iteration) {
    //cout << "iteration: " << iteration << endl;
    //Check for when rays go inbetween triangles
    if(arg == nullptr || arg->start == nullptr || arg->end == nullptr) {
        //cout << "null" << endl;
        return;
    }
    
    //Add intersections to ray
    findIntersection(*arg);
    //cout << *arg << endl;
    
    if(iteration > 0) {
        return;
    }
    
    if(arg->intSectPoint == nullptr) {
        //cout << "nullptr" << endl;
        return;
    }
    
    if( (arg->start->vec3 - arg->intSectPoint->vec3) < 0.1 ||
       -1*(arg->start->vec3 - arg->intSectPoint->vec3) > 0.1 ) {
        //cout << "intersects with itself" << endl;
        return;
    }
    //If the ray hits a diffuse triangle
    if(arg->endTri && arg->endTri->surf.reflectionType == 0) {
        arg->monteCarloRay = monteCarloRayTracing(arg);
        rayTracing(arg->monteCarloRay, iteration +1);

    }
    //If the ray hits a diffuse sphere
    else if(arg->endSphere && arg->endSphere->surf.reflectionType == 0) {

        arg->monteCarloRay = monteCarloRayTracing(arg);
        rayTracing(arg->monteCarloRay, iteration +1);
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
        rayTracing(arg->reflectedRay, iteration + 1);
    }
}

matrix<double> Scene::transformToLocalCoordinateSystem(Ray *arg) {

    Vector3 I = (*arg->end - *arg->start).vec3;

    matrix<double> transform(4,4);

    Vector3 z = (arg->endTri ? arg->endTri->normal : arg->endSphere->calcNormal(*arg)).normalize();
    Vector3 x = (I - dotProduct(I, z) * z).normalize();
    Vector3 y = crossProduct(-1*x, z).normalize();
    
    //Rotation to new coordinate system
    matrix<double> rotation(x, y, z);
    
    
    //Translation to new coordinate system
    Vector3 col1 = Vector3(1,0,0);
    Vector3 col2 = Vector3(0,1,0);
    Vector3 col3 = Vector3(0,0,1);
    matrix<double> translation(col1, col2, col3, -1*(arg->intSectPoint->vec3));
    
    transform.multiply(translation, rotation); // DO NOT CHANGE ORDER
    
    //transform.printm();

    return transform;
}

Ray* Scene::monteCarloRayTracing(Ray *arg) {
    //cout << "MONTE CARLO" << endl;
    //Setting up the estimator by generating 2 random numbers [0,1]

    double randX = (*dis)(*gen);
    double randY = (*dis)(*gen);
    double PI = 3.14;
    
    //Monte Carlo solution with a cosine estimator
    double azimuth = 2*PI*randX;
    //azimuth = (azimuth*360)/2*PI;
    double inclination = asin(sqrt(randY));
    //inclination = (inclination*360)/(2*PI); //To degrees
    
    Vector3 normal = (arg->endTri ? arg->endTri->normal : arg->endSphere->calcNormal(*arg)).normalize();
    glm::vec3 normalGLM((float)normal.x, (float)normal.y, (float)normal.z);
    glm::vec3 helper = normalGLM + glm::vec3(1,1,1);
    glm::vec3 tangent = glm::normalize(glm::cross(normalGLM, helper));
    
    glm::vec3 random_direction = normalGLM;
    random_direction = glm::normalize(glm::rotate(random_direction, (float) inclination, tangent));
    random_direction = glm::normalize(glm::rotate(random_direction, (float) azimuth, normalGLM));
    
    
    
    
    //Inclination rotation, rotation along y-axis
//    Vector3 col1 = Vector3(cos(inclination), 0, sin(inclination));
//    Vector3 col2 = Vector3(0 ,1 , 0);
//    Vector3 col3 = Vector3(-sin(inclination),0, cos(inclination));
//    matrix<double> inclinationRotation(col1, col2, col3);
//
//    glm::mat4x4();

//
//    //Azimuth rotation, rotation along z-axis
//    col1 = Vector3(cos(azimuth), -sin(azimuth), 0);
//    col2 = Vector3(sin(azimuth), cos(azimuth), 0);
//    col3 = Vector3(0 ,0 ,1 );
//    matrix<double> azimuthRotation(col1, col2, col3);
//
//    //Total rotation. This is the local random outgoing direction transformation
//    matrix<double> rotation(4,4);
//    rotation.multiply(azimuthRotation, inclinationRotation).normalize();

    
    //Getting outgoing direction by transforming to local coordinate system
    //matrix<double> changeCoords = transformToLocalCoordinateSystem(arg);

    
    //Check if inverse is not possible, terminate ray
//    if(changeCoords.determinant(4) <= 0) {
//        cout << "singular matrix!" << endl;
//        return nullptr;
//    }
    
    //Transform to global coordinate system
    //changeCoords.normalize();
    
    //Incoming direction
    Vector3 inDirGlobal = (*arg->end - *arg->start).vec3.normalize();
    //cout << inDir << endl;
    
    //Getting transformation matrix
//    matrix<double> inGlobal(inDirGlobal);
//    inGlobal.transpose();
    
    
    //Transform to local coordinate system
 //   Vector3 inDirLocal = changeCoords.multiply(inDirGlobal).normalize();
    //cout << inDirLocal << endl;
    
    //Apply rotation
  //  Vector3 outDirLocal = rotation.multiply(inDirLocal).normalize();
    //cout << outDirLocal << endl;
    
    //Transform to global coordinate system
 //   changeCoords.invert();
  //  Vector3 outDirGlobal = changeCoords.multiply(outDirLocal).normalize();
    //cout << "outDIrGlobal: " << outDirGlobal << endl;
    Vector3 outDirGlobal = Vector3((double)random_direction.x, (double)random_direction.y, (double)random_direction.z );
    
    //Add new ray to the tree
    Vertex* endVertex = new Vertex(arg->intSectPoint->vec3 + outDirGlobal);
    Ray *outRay = new Ray(arg->intSectPoint, endVertex);
    //cout << outRay << " END OF MONTE CARLO " << endl;
    return outRay;
}
