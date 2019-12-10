//
//  Surface.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-02.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Surface_hpp
#define Surface_hpp

#include <stdio.h>
#include "glm.hpp"

using namespace glm;
using namespace std;

class Ray;

class Surface {
  
public:
	Surface(int inReflectionType = 0, vec3 col = vec3(1.0f, 1.0f, 1.0f), float inRoughness = 0.0f)
		: reflectionType(inReflectionType), color(col), roughness(inRoughness)
	{
        if(inReflectionType == 2) { refractionIndex = 1.53f; }
        
    }
    
    //Diffuse reflection = 0, Perfect reflection = 1, perfect refraction = 2
	int reflectionType = 0;
	vec3 color;

    float refractionIndex = 1.0f; //air
    
	float reflectionCo = 0.8f;
    float roughness = 0.0f;

};

#endif /* Surface_hpp */
