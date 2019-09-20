//
//  Camera.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

class Camera {
public:
    Vertex eyeL, eyeR;
    bool activeEye = true; // if false, left eye. If true, right eye
    Camera(Vertex inL = Vertex(0.0,0.0,0.0), Vertex inR = Vertex(0.0,0.1,0.0))
    : eyeL(inL), eyeR(inR) {}
    
    matrix<Pixel> plane;
    
    void render();
    void createImage();
};

#endif /* Camera_hpp */
