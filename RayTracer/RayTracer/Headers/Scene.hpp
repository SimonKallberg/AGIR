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

class Scene {
public:
    std::vector<Triangle> scene;
    std::vector<Sphere> spheres;
    std::vector<PointLight> pointLights;
    
    void initialize();
    void addTetrahedron(Vertex top, Vertex corner1, Vertex corner2, Vertex corner3, ColorDbl incolor);
    void addSphere(Vertex inCenter, double radius, ColorDbl inColor);
    void addPointLight(Vertex inCenter);
    bool shootShadowRay(Vertex &inV);
    
    Vertex* findInterTri(Ray &arg, Triangle &t1);
    Vertex* findInterSphere(Ray &arg, Sphere &s1);
};

#endif
