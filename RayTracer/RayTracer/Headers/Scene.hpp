//
//  Scene.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Vertex.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "PointLight.hpp"
#include "ColorDbl.hpp"
#include <algorithm>
#include <iterator>
#include "matrix.hpp"
#include <random>
#include "glm.hpp"
#include "transform.hpp"
#include "rotate_vector.hpp"


class Scene {
public:
    //Random generator
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::uniform_real_distribution<float>* dis;
    std::mt19937* gen;
    
    Scene() {
         //Standard mersenne_twister_engine seeded with rd()
        gen = new std::mt19937(rd());
        dis = new std::uniform_real_distribution<float>(0.0, 1.0);
        
    }
    std::vector<Triangle> scene;
    std::vector<Sphere> spheres;
    std::vector<PointLight> pointLights;
    
    void initialize();
    void addTetrahedron(Vertex inV, double scale, ColorDbl incolor, int reflType = 0);
    void addSphere(Vertex inCenter, double radius, ColorDbl inColor, int inReflType);
    void addPointLight(Vertex inCenter);
    
    bool shootShadowRay(Vertex &inV);
    Vertex* findIntersection(Ray &arg);
    ColorDbl traceRay(Ray* arg, int iteration);
    Ray* traceRayMonteCarlo(Ray *arg);
    Ray* traceRayPerfectReflection(Ray &inRay);
    ColorDbl getLambertianSurfaceColor(Ray &endRay);
};


#endif
