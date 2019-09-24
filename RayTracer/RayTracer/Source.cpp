#include <iostream>
#include <vector>
#include <cstdio>
#include "bitmap_image.hpp"
#include "matrix.hpp"

const int CAMERA_WIDTH = 800;
const int CAMERA_HEIGHT = 800;

class Vertex {
public:
	Vertex(double inX, double inY, double inZ, double inW = 1.0)
     : x(inX), y(inY), z(inZ), w(inW) {}
	double x, y, z, w;
    friend Vertex operator+(Vertex lhs, Vertex rhs);
    friend Vertex operator-(Vertex lhs, Vertex rhs);

	friend std::ostream& operator<<(std::ostream& out, const Vertex& v1);
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
	friend std::ostream& operator<<(std::ostream& out, const Direction& v1);
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

    Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inCol = ColorDbl(0.5,0.5,0.5))
    : v0(inV0), v1(inV1), v2(inV2), color(inCol)
    {
        normal = calcNormal();
    }
	bool rayIntersection(Ray arg1);
    Direction calcNormal();

	friend std::ostream& operator<<(std::ostream& out, const Triangle& v1);

};

class Ray {
public:
	Ray(Vertex* s, Vertex* e)
		: start(s), end(e)
	{}

	Vertex* start;
	Vertex* end;
    Vertex* intSectPoint = nullptr;

	Triangle* endTri = nullptr;
	ColorDbl color = ColorDbl(0.0,0.0,0.0);

	friend std::ostream& operator<<(std::ostream& out, const Ray& v1);
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
	Scene* theScene = nullptr;
	bool activeEye = true; // if false, left eye. If true, right eye
	Camera(Scene* inScene, Vertex inL = Vertex(-2.0, 0.0, 0.0), Vertex inR = Vertex(-1.0, 0.0, 0.0))
    : theScene(inScene), eyeL(inL), eyeR(inR) {}

	Vertex c1 = Vertex(0.0, -1.0, -1.0); 
	Vertex c2 = Vertex(0.0, 1.0, -1.0);
	Vertex c3 = Vertex(0.0, 1.0, 1.0);
	Vertex c4 = Vertex(0.0, -1.0, 1.0);

	

	matrix<Pixel> plane;
   
	Ray calcRay(int x, int y);
	void render();
	void createImage();
};

int main()
{
	Scene myScene;
	myScene.initialize();

    //Can't run this on Ylvas computer - lack of memory?????????
    Camera myCamera(&myScene);

	Direction v1 = Direction(2.0, 3.0, 4.0);
	Direction v2 = Direction(3.0, 2.0, 2.0);
	Direction v3 = crossProduct(v1, v2);
	cout << "crossad v3: " << v3 << endl;
	cout << "Dottad v3: " << dotProduct(v1, v2) << endl;
	//myScene.findInterTri();
	myCamera.render();
    myCamera.createImage();

	return 0;
}


Vertex operator+(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}
Vertex operator-(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}
std::ostream& operator<<(std::ostream& out, const Vertex& v1) {
	out << "(" << v1.x << "," << v1.y << "," << v1.z << ")" << std::endl;
	return out;
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


std::ostream& operator<<(std::ostream& out, const Direction& v1) {
	out << v1.x << " " << v1.y << " " << v1.z << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Ray& v1) {
	out << *v1.start << " " << *v1.end << endl;
	return out;
}

double dotProduct(Direction lhs, Direction rhs) {
    return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z;
}

Direction Triangle::calcNormal() {
    Direction vector1 = Direction(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
    Direction vector2 = Direction(v0.x-v2.x, v0.y-v2.y, v0.z-v2.z);
    //Cross product to get normal
    Direction normal = crossProduct(vector1, vector2);
    //Normalize
    double length = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    normal = Direction(normal.x/length, normal.y/length, normal.z/length);
    //std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;
}

std::ostream& operator<<(std::ostream& out, const Triangle& v1) {
	out << v1.v0 << " " << v1.v1 << " " << v1.v2 << endl;
	return out;
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
//	cout << "OUR RAY: " << arg << " jag e klar " << endl;


    for(int i = 0; i < scene.size(); i++) {
        if(scene[i].rayIntersection(arg)) {
            t1 = scene[i];
//			cout << "our trianglus: " << scene[i] << endl;
            return arg.intSectPoint;
        }
    }
	return nullptr;
}

Ray Camera::calcRay(int x, int y) {
	double deltaWidth = (c1.y - c3.y) / CAMERA_WIDTH;
	double deltaHeight = (c1.z - c3.z) / CAMERA_HEIGHT;

	Vertex localCoord = Vertex(0.0, x*deltaWidth, y*deltaHeight);
	//cout << localCoord << endl;
	Vertex* end = new Vertex(c1 + localCoord);

	Ray myRay(&eyeL, end);
	//cout << eyeL << " " << *end << endl;
	return myRay;
}

void Camera::render()
{
/*	for (int x = 0; x < CAMERA_WIDTH; x++) 
	{
		for (int y = 0; y < CAMERA_HEIGHT; y++)
		{
			Triangle temp(Vertex(1.0, 1.0, 0.0), Vertex(1.0, -1.0, 0.0), Vertex(-1.0, -1.0, 0.0));
			Ray myRay = calcRay(x, y);
			theScene->findInterTri(myRay, temp);
			plane(x, y).color = temp.color;

		}
	}
	*/
	/*Triangle temp(Vertex(1.0, 1.0, 0.0), Vertex(1.0, -1.0, 0.0), Vertex(-1.0, -1.0, 0.0));
	Ray myRay = calcRay(0,0);
	//std::cout << *myRay.start << " " << *myRay.end << endl;
	theScene->findInterTri(myRay, temp);
	std::cout << temp << endl;
	plane(0, 0).color = temp.color;*/
}

void Camera::createImage()
{
	bitmap_image image(CAMERA_WIDTH, CAMERA_HEIGHT);
	image.clear();
    // set background to orange
    //image.set_all_channels(255, 150, 50);
	
    //Set pixels to the camera plane
    for(int x = 0; x < 800; x++) {
        for(int y = 0; y < 800; y++) {
            //cout << plane(x,y).color.r << " " << plane(x,y).color.g << " " << plane(x,y).color.b << endl;
            rgb_t color = make_colour(plane(x,y).color.r*255, plane(x,y).color.g*255, plane(x,y).color.b*255);
            image.set_pixel( x,  y, color);
            //cout << image.get_pixel(x, y).red << endl;
        }
    }
    cout << "Saving image..." << endl;
	image.save_image("raytracing.bmp");
}
