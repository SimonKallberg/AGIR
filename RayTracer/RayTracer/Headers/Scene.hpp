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
#include "vec3.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "PointLight.hpp"
#include "vec3.hpp"
#include <algorithm>
#include <iterator>
#include "matrix.hpp"
#include <random>
#include "glm.hpp"
#include "transform.hpp"
#include "rotate_vector.hpp"

using namespace glm;
using namespace std;


class Scene {
public:
    //Random generator
    random_device rd;  //Will be used to obtain a seed for the random number engine
    uniform_real_distribution<float>* dis;
    mt19937* gen;
    
    Scene() {
         //Standard mersenne_twister_engine seeded with rd()
        gen = new mt19937(rd());
        dis = new uniform_real_distribution<float>(0.0f, 1.0f);
        
    }
    vector<Triangle> scene;
    vector<Sphere> spheres;
    vector<PointLight> pointLights;
    vector<Triangle> lights;
    
    void initialize();
    void addTetrahedron(vec3 inV, float scale, vec3 incolor, int reflType = 0, float inRoughness = 0.0f);
    void addSphere(vec3 inCenter, float radius, vec3 inColor, int inReflType, float inRoughness = 0.0f);
    void addPointLight(vec3 inCenter);
    void addAreaLight(vec3 v0, vec3 v1, vec3 v2, vec3 v3);
    glm::vec3 getPointOnAreaLight(float u, float v);
    
    bool shootShadowRay(vec3 &inV);
    vec3* findIntersection(Ray &arg);
    vec3 traceRay(Ray* arg, int iteration);
    Ray* traceRayMonteCarlo(Ray *arg);
    Ray* traceRayPerfectReflection(Ray &inRay);
    float traceRayRefraction(Ray *arg);
    vec3 getLambertianSurfaceColor(Ray &endRay);
    vec3 getOrenNayarSurfaceColor(Ray &endRay);
};


#endif
