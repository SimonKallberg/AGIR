#include <iostream>
#include <vector>
#include <cstdio>
#include "bitmap_image.hpp"
#include "matrix.hpp"

class Vertex {
public:
	Vertex(double inX, double inY, double inZ, double inW = 1.0)
     : x(inX), y(inY), z(inZ), w(inW) {}
	double x, y, z, w;
    friend Vertex operator+(Vertex lhs, Vertex rhs);
    friend Vertex operator-(Vertex lhs, Vertex rhs);
};

class Direction {
public:
	double x, y, z;
    
    Direction(double inX, double inY, double inZ)
    : x(inX), y(inY), z(inZ) {}
    //Conversion from vertex to direction
    Direction(Vertex v)
    : x(v.x), y(v.y), z(v.z) {}
    
    friend Direction crossProduct(Direction vector1, Direction vector2);
    friend Direction operator+(Direction lhs, Direction rhs);
    friend Direction operator-(Direction lhs, Direction rhs);
    friend double dotProduct(Direction lhs, Direction rhs);
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
	bool rayIntersection(Ray arg1);
    Direction calcNormal();

};

class Ray {
public:
	Vertex* start;
	Vertex* end;
    Vertex* intSectPoint;

	Triangle* endTri;
	ColorDbl color;
};

class Scene {
public:
	std::vector<Triangle> scene;

	void initialize();

	Vertex* findInterTri(Ray arg, Triangle &t1);
};

class Pixel {
public:
    Pixel(ColorDbl inCol);
    Pixel(double r = 0, double g = 0, double b = 0)
    : color(r, g, b) {}
	ColorDbl color;
	std::vector<Ray> rays;

};

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

int main()
{
	Scene myScene;
	myScene.initialize();
    Camera myCamera;
    myCamera.createImage();

	return 0;
}

Vertex operator+(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}
Vertex operator-(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

Direction operator+(Direction lhs, Direction rhs) {
    return Direction(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}

Direction operator-(Direction lhs, Direction rhs) {
    return Direction(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

Direction crossProduct(Direction vector1, Direction vector2) {
    return Direction((vector1.y*vector2.z)-(vector1.z*vector2.y),
                     -((vector1.x*vector2.z)-(vector1.z*vector2.x)),
                     (vector1.x*vector2.y)-(vector1.y*vector2.x));
}

double dotProduct(Direction lhs, Direction rhs) {
    return lhs.x*rhs.x+lhs.y+rhs.y+lhs.z+rhs.z;
}

Direction Triangle::calcNormal() {
    Direction vector1 = Direction(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
    Direction vector2 = Direction(v0.x-v2.x, v0.y-v2.y, v0.z-v2.z);
    //Cross product to get normal
    Direction normal = crossProduct(vector1, vector2);
    //Normalize
    double length = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    normal = Direction(normal.x/length, normal.y/length, normal.z/length);
    std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;
}

bool Triangle::rayIntersection(Ray p)
{
    Direction T = *p.start-v0;
    Direction E1 = v1-v0;
    Direction E2 = v2 - v0;
    Direction D = *p.end - *p.start;
    Direction P = crossProduct(D, E2);
    Direction Q = crossProduct(T, E1);
    Direction intersection = Direction(dotProduct(Q, E2)/dotProduct(P, E1),
                            dotProduct(P, T)/dotProduct(P, E1),
                            dotProduct(Q, D)/dotProduct(P, E1));
    //Check if variables are in triangle area -> intersection!
    if(intersection.y + intersection.z < 1 && intersection.y >= 0 && intersection.z >= 0) {
        p.endTri = this;
        return true;
    }
    return false;
}

void Scene::initialize()
{
	std::cout << "Setting up triangles...." << std::endl;

    //Setting up a room shaped as a polygon
    // Vägg numero uno
	scene.push_back(Triangle(Vertex(-3,0,5), Vertex(0,6,5), Vertex(-3,0,-5)));
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(0,6,-5), Vertex(-3,0,-5)));
    scene.push_back(Triangle(Vertex(0,6,5), Vertex(10,6,5), Vertex(0,6,-5)));
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(10,6,-5), Vertex(0,6,-5)));
    scene.push_back(Triangle(Vertex(10,6,5), Vertex(13,0,5), Vertex(10,6,-5)));
    scene.push_back(Triangle(Vertex(13,0,5), Vertex(13,0,-5), Vertex(10,6,-5)));
    
    //Vägg numero dos
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,5), Vertex(-3,0,5)));
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,-6,-5), Vertex(0,-6,5)));
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,5), Vertex(0,-6,5)));
    scene.push_back(Triangle(Vertex(0,-6,-5), Vertex(10,-6,-5), Vertex(10,-6,5)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,-6,-5)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,-5), Vertex(13,0,5)));
    
    //Toppen
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(0,6,5), Vertex(-3,0,5)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,6,5), Vertex(0,6,5)));
    scene.push_back(Triangle(Vertex(0,-6,5), Vertex(10,-6,5), Vertex(10,6,5)));
    scene.push_back(Triangle(Vertex(10,-6,5), Vertex(13,0,5), Vertex(10,6,5)));
    
    //Botten
    scene.push_back(Triangle(Vertex(-3,0,-5), Vertex(0,6,-5), Vertex(0,-6,-5)));
    scene.push_back(Triangle(Vertex(0,6,-5), Vertex(10,6,-5), Vertex(0,-6,-5)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(10,-6,-5), Vertex(0,-6,-5)));
    scene.push_back(Triangle(Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5)));
    
}

Vertex* Scene::findInterTri(Ray arg, Triangle &t1)
{
    for(int i = 0; i < scene.size(); i++) {
        if(scene[i].rayIntersection(arg)) {
            t1 = scene[i];
            return arg.intSectPoint;
        }
    }
	return nullptr;
}

void Camera::render()
{
}

void Camera::createImage()
{
	bitmap_image image(800, 800);
    // set background to orange
    image.set_all_channels(255, 150, 50);
    image.save_image("ylvasellinghej.bmp");

    //Set pixels to the camera plane
    for(int x = 0; x < 800; x++) {
        for(int y = 0; y < 800; y++) {
            //cout << plane(x,y).color.r << " " << plane(x,y).color.g << " " << plane(x,y).color.b << endl;
            rgb_t color = make_colour(plane(x,y).color.r, plane(x,y).color.g, plane(x,y).color.b);
            image.set_pixel( x,  y, jet_colormap[x]);
            //cout << image.get_pixel(x, y).red << endl;
        }
    }
    cout << "Saving image..." << endl;
	image.save_image("raytracing.bmp");
}
