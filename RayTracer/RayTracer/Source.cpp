#include <iostream>
#include <vector>
#include <cstdio>
#include "bitmap_image.hpp"


template<typename T>
using matrix = std::vector<std::vector<T>>;

class Vertex {
public:
	Vertex(double inX, double inY, double inZ, double inW = 1.0) : x(inX), y(inY), z(inZ), w(inW) {}
	double x, y, z, w;
};

class Direction {
public:
	double x, y, z;
    
    Direction(double inX, double inY, double inZ)
    : x(inX), y(inY), z(inZ) {}
};

class ColorDbl {
public:
	double r, g, b;
    
    ColorDbl(double inR, double inG, double inB)
    : r(inR), g(inG), b(inB){}
};

class Ray;
 
class Triangle {
public:
    Vertex v0, v1, v2;
    ColorDbl color;
    Direction normal = Direction(0.0,0.0,0.0);

    Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inCol = ColorDbl(0.0,0.0,0.0))
    : v0(inV0), v1(inV1), v2(inV2), color(inCol)
    {
        normal = calcNormal();
    }
	void rayIntersection(Ray arg1);
    Direction calcNormal();

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

	void initialize();

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
	Scene myScene;
	myScene.initialize();
	

	return 0;
}

Direction Triangle::calcNormal() {
    Direction vector1 = Direction(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
    Direction vector2 = Direction(v0.x-v2.x, v0.y-v2.y, v0.z-v2.z);
    //Cross product to get normal
    Direction normal = Direction((vector1.y*vector2.z)-(vector1.z*vector2.y),
                                 -((vector1.x*vector2.z)-(vector1.z*vector2.x)),
                                 (vector1.x*vector2.y)-(vector1.y*vector2.x));
    //Normalize
    double length = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    normal = Direction(normal.x/length, normal.y/length, normal.z/length);
    std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;
}

void Triangle::rayIntersection(Ray arg1)
{
}

void Scene::initialize()
{
	std::cout << "Setting up triangles...." << std::endl;

    //Setting up a room shaped as a polygon
    // Vägg numero uno
	obj.push_back(Triangle(Vertex(-3,0,5), Vertex(0,6,5), Vertex(-3,0,-5)));
    obj.push_back(Triangle(Vertex(0,6,5), Vertex(0,6,-5), Vertex(-3,0,-5)));
    obj.push_back(Triangle(Vertex(0,6,5), Vertex(10,6,5), Vertex(0,6,-5)));
    obj.push_back(Triangle(Vertex(10,6,5), Vertex(10,6,-5), Vertex(0,6,-5)));
    obj.push_back(Triangle(Vertex(10,6,5), Vertex(13,0,5), Vertex(10,6,-5)));
    obj.push_back(Triangle(Vertex(13,0,5), Vertex(13,0,-5), Vertex(10,6,-5)));
    
    //Vägg numero dos
    obj.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,5), Vertex(-3,0,5)));
    obj.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,-5), Vertex(0,-6,5)));
    obj.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,5), Vertex(0,-6,5)));
    obj.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,-5), Vertex(10,-6,5)));
    obj.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,-6,-5)));
    obj.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,-5), Vertex(13,0,5)));
    
    //Toppen
    obj.push_back(Triangle(Vertex(0,-6,5), Vertex(0,6,5), Vertex(-3,0,5)));
    obj.push_back(Triangle(Vertex(0,-6,5), Vertex(10,6,5), Vertex(0,6,5)));
    obj.push_back(Triangle(Vertex(0,-6,5), Vertex(10,-6,5), Vertex(10,6,5)));
    obj.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,6,5)));
    
    //Botten
    obj.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,6,-5), Vertex(0,-6,-5)));
    obj.push_back(Triangle(Vertex(0,6,-5), Vertex(10,6,-5), Vertex(0,-6,-5)));
    obj.push_back(Triangle(Vertex(10,6,-5), Vertex(10,-6,-5), Vertex(0,-6,-5)));
    obj.push_back(Triangle(Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5)));
    
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
