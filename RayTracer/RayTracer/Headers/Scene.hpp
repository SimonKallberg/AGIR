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

class Scene {
public:
    std::vector<Triangle> scene;
    std::vector<Sphere> spheres;
    std::vector<PointLight> pointLights;
    
    void initialize();
    void addTetrahedron(Vertex inV, double scale, ColorDbl incolor);
    void addSphere(Vertex inCenter, double radius, ColorDbl inColor);
    void addPointLight(Vertex inCenter);
    bool shootShadowRay(Vertex &inV);
    
    Vertex* findInterObj(Ray &arg, Triangle &t1, Sphere &s1);
};

#endif
