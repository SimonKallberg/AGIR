//
//  Scene.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Vertex.hpp"
#include "Ray.hpp"
#include <vector>
#include "Triangle.hpp"

class Scene {
public:
    std::vector<Triangle> scene;
    
    void initialize();
    
    Vertex* findInterTri(Ray arg, Triangle &t1);
};

#endif Scene_hpp
