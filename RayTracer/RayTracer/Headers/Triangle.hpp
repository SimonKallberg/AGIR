//
//  Triangle.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include <cmath>
#include "Vertex.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"
#include "ColorDbl.hpp"
#include "Surface.hpp"
#include "glm.hpp"
#include "Geometry.hpp"

using namespace std;
using namespace glm;

class Scene;

class Triangle : public Geometry {
public:
    
	Triangle(vec3 inV0 = vec3(1.0f, 1.0f, 0.0f), vec3 inV1 = vec3(1.0f, -1.0f, 0.0f), vec3 inV2 = vec3(-1.0f, -1.0f, 0.0f), vec3 inCol = vec3(0.5f, 0.5f, 0.5f), Material refType = LAMBERTIAN, float inRoughness = 1.0f)
		: v0(inV0), v1(inV1), v2(inV2), objectMaterial(refType), objectColor(inCol)
	{
		normal = calcNormal();
	}

	bool rayIntersection(Ray &ray) override;
    Material material() override;
    glm::vec3 color() override;
    float roughness() override;
	vec3 calcNormal();
    void flipNormal();

	friend ostream& operator<<(ostream& out, const Triangle& v);
    
private:
    Material objectMaterial;
    vec3 objectColor = vec3(1.0f);
    float objectRoughness;
    vec3 normal = vec3(0.0f, 0.0f, 0.0f);
    vec3 v0, v1, v2 = vec3(0.0f, 0.0f, 0.0f);
};

#endif
