//
//  main.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-20.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include "bitmap_image.hpp"
#include "matrix.hpp"
#include "bitmap.h"

int main()
{
    Scene myScene;
    myScene.initialize();
    Camera myCamera;
    
    //myScene.findInterTri();
    myCamera.createImage();
    Bitmap myImageTest;
    PixelMatrix mypixelimage;
    mypixelimage.at(0).push_back(Pixel(255, 255, 255));
    
    myImageTest.fromPixelMatrix(mypixelimage);
    myImageTest.save("hello.bmp");
    
    
    
    return 0;
}
