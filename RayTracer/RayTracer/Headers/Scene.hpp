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

class Scene {
public:
    std::vector<Triangle> scene;
    std::vector<Sphere> spheres;
    std::vector<PointLight> pointLights;
    
    void initialize();
    void addTetrahedron(Vertex inV, double scale, ColorDbl incolor, int reflType = 0);
    void addSphere(Vertex inCenter, double radius, ColorDbl inColor, int inReflType);
    void addPointLight(Vertex inCenter);
    bool shootShadowRay(Vertex &inV);
    
    Vertex* findIntersection(Ray &arg);
    void rayTracing(Ray* arg);
    matrix<double> transformToLocalCoordinateSystem(Ray &arg);
    Ray monteCarloRayTracing(Ray &arg);
};


#endif
