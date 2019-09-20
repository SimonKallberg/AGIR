//
//  Camera.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Camera.hpp"

void Camera::render()
{
}

void Camera::createImage()
{
    bitmap_image image(800, 800);
    image.clear();
    // set background to orange
    image.set_all_channels(255, 150, 50);
    
    //Set pixels to the camera plane
    for(int x = 0; x < 800; x++) {
        for(int y = 0; y < 800; y++) {
            //cout << plane(x,y).color.r << " " << plane(x,y).color.g << " " << plane(x,y).color.b << endl;
            //rgb_t color = make_colour(plane(x,y).color.r*255, plane(x,y).color.g*255, plane(x,y).color.b*255);
            //image.set_pixel( x,  y, color);
            //cout << image.get_pixel(x, y).red << endl;
        }
    }
    cout << "Saving image..." << endl;
    image.save_image("raytracing.bmp");
}
