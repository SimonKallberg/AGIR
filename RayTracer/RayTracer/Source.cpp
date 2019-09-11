#include <iostream>
#include <vector>
#include <cstdio>
#include "bitmap_image.hpp"


template<typename T>
using matrix = std::vector<std::vector<T>>;

class Vertex {
public:
	Vertex(double inX, double inY, double inZ, double inW) : x(inX), y(inY), z(inZ), w(inW) {}
	double x, y, z, w;
};

class Direction {
public:
	double x, y, z;
};

class ColorDbl {
public:
	double r, g, b;
};

class Ray;
 
class Triangle {
public:
	Vertex v0, v1, v2;
	ColorDbl color;
	Direction normal;

	void rayIntersection(Ray arg1);
};

class Ray {
public:
	Vertex* start;
	Vertex* end;

	Triangle endTri;
	ColorDbl color;
};

class Scene {
public:
	std::vector<Triangle> obj;

	Vertex findInterTri(Ray arg, Triangle &t1);
};

class Pixel {
public:
	ColorDbl color;
	std::vector<Ray> rays;

};

class Camera {
public:
	Vertex eyeL, eyeR;

	bool activeEye; // if false, left eye. If true, right eye
	
	//matrix<Pixel> plane;
	Pixel plane[800][800];

	void render();
	void createImage();
};

int main()
{

	

	return 0;
}

void Triangle::rayIntersection(Ray arg1)
{
}

Vertex Scene::findInterTri(Ray arg, Triangle &t1)
{
	Vertex v1(0,0,0,0);


	return v1;
}

void Camera::render()
{
}

void Camera::createImage()
{
	bitmap_image image(200, 200);

	// set background to orange
	image.set_all_channels(255, 150, 50);

	image_drawer draw(image);

	draw.pen_width(3);
	draw.pen_color(255, 0, 0);
	draw.circle(image.width() / 2, image.height() / 2, 50);

	draw.pen_width(1);
	draw.pen_color(0, 0, 255);
	draw.rectangle(50, 50, 150, 150);

	image.save_image("output.bmp");
}
