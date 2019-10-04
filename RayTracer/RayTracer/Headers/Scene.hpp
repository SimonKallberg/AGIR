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
    std::vector<Triangle> tetrahedra;
    
    void initialize();
    void addTetrahedron(Vertex inV, ColorDbl incolor);
    void addSphere(Vertex inCenter, double radius, ColorDbl inColor);
    void addPointLight(Vertex inCenter);
    bool shootShadowRay(Vertex &inV);
    
    Vertex* findInterTri(Ray &arg, Triangle &t1);
    Vertex* findInterSphere(Ray &arg, Sphere &s1);
    Vertex* findInterTetra(Ray &arg, Triangle &t1);
    Vertex* findInterObj(Ray &arg, Triangle &t1, Sphere &s1);
};

#endif
