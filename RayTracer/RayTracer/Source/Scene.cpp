//
//  Scene.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Scene.hpp"



void Scene::initialize()
{
    std::cout << "Setting up triangles...." << std::endl;
    
    //Setting up a room shaped as a polygon
    
    //Wall2 - matte light pink
    scene.push_back(Triangle(vec3(0.0f, 6.0f, 5.0f),vec3(10.0f, 6.0f, 5.0f), vec3(0.0f, 6.0f ,-5.0f), vec3(0.23f, 0.31f, 0.27f)));
    scene.push_back(Triangle(vec3(10.0f, 6.0f, 5.0f),vec3(10.0f, 6.0f , -5.0f),vec3(0.0f, 6.0f ,-5.0f),vec3(0.94f, 0.66f, 0.73f)));
	
    //Wall 3 - matte blue
    scene.push_back(Triangle(vec3(10.0f, 6.0f, 5.0f), vec3(13.0f, 0.0f, 5.0f), vec3(10.0f, 6.0f, -5.0f), vec3(1.0f, 1.0f, 0.0f)));
    scene.push_back(Triangle(vec3(13.0f, 0.0f, 5.0f), vec3(13.0f, 0.0f, -5.0f), vec3(10.0f, 6.0f, -5.0f), vec3(0.36f, 0.45f, 0.63f)));
    
    //Wall 4 - dark matte pink
    scene.push_back(Triangle(vec3(-3.0f, 0.0f, -5.0f), vec3(0.0f, -6.0f, 5.0f), vec3(-3.0f, 0.0f, 5.0f), vec3(0.92f, 0.64f, 0.59f)));
    scene.push_back(Triangle(vec3(-3.0f, 0.0f, -5.0f), vec3(0.0f, -6.0f, -5.0f), vec3(0.0f, -6.0f, 5.0f), vec3(0.76f, 0.4f, 0.5f)));

	//Wall 5 - dark green
    scene.push_back(Triangle(vec3(0.0f,-6.0f,-5.0f), vec3(10.0f,-6.0f,5.0f), vec3(0.0f,-6.0f,5.0f), vec3(0.94f, 0.66f, 0.73f)));
    scene.push_back(Triangle(vec3(0.0f,-6.0f,-5.0f), vec3(10.0f,-6.0f,-5.0f), vec3(10.0f,-6.0f,5.0f), vec3(0.23f, 0.31f, 0.27f)));
	
    //Wall 6 - green
    scene.push_back(Triangle(vec3(10.0f,-6.0f,-5.0f), vec3(13.0f,0.0f,5.0f), vec3(10.0f,-6.0f,5.0f), vec3(0.76f, 0.4f, 0.5f)));
    scene.push_back(Triangle(vec3(10.0f,-6.0f,-5.0f), vec3(13.0f,0.0f,-5.0f), vec3(13.0f,0.0f,5.0f), vec3(0.92f, 0.64f, 0.59f)));
    
    //celing - white
    scene.push_back(Triangle(vec3(0.0f, -6.0f, 5.0f), vec3(0.0f,6.0f,5.0f), vec3(-3.0f, 0.0f, 5.0f), vec3(1.0f, 1.0f, 1.0f)));
    scene.push_back(Triangle(vec3(0.0f,-6.0f,5.0f), vec3(10.0f,6.0f,5.0f), vec3(0.0f,6.0f,5.0f), vec3(1.0f, 1.0f, 1.0f)));
    scene.push_back(Triangle(vec3(0.0f, -6.0f, 5.0f), vec3(10.0f,-6.0f,5.0f), vec3(10.0f, 6.0f, 5.0f), vec3(1.0f, 1.0f, 1.0f)));
    scene.push_back(Triangle(vec3(10.0f,-6.0f,5.0f), vec3(13.0f,0.0f,5.0f), vec3(10.0f,6.0f,5.0f), vec3(1.0f, 1.0f, 1.0f)));
    
    //floor - white
    scene.push_back(Triangle(vec3(-3.0f,0.0f,-5.0f), vec3(0.0f,6.0f,-5.0f), vec3(0.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    scene.push_back(Triangle(vec3(0.0f,6.0f,-5.0f), vec3(10.0f,6.0f,-5.0f), vec3(0.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    scene.push_back(Triangle(vec3(10.0f,6.0f,-5.0f), vec3(10.0f,-6.0f,-5.0f), vec3(0.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    scene.push_back(Triangle(vec3(10.0f,6.0f,-5.0f), vec3(13.0f,0.0f,-5.0f), vec3(10.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    
    // Wall 1 - yellow
    scene.push_back(Triangle(vec3(-3.0f, 0.0f, 5.0f), vec3(0.0f, 6.0f, 5.0f), vec3(-3.0f, 0.0f, -5.0f), vec3(0.36f, 0.45f, 0.63f)));
    scene.push_back(Triangle(vec3(0.0f, 6.0f, 5.0f), vec3(0.0f, 6.0f, -5.0f), vec3(-3.0f, 0.0f, -5.0f), vec3(1.0f, 1.0f, 0.0f)));
}



void Scene::addTetrahedron(vec3 inV, float scale, vec3 incolor, int reflType, float inRoughness) {
	
    //Closest to camera
	vec3 corner1 = inV + scale*vec3(-sqrt(8.0f/9.0f), 0.0, -(1.0f/3.0f));
    //Right back
	vec3 corner2 = inV + scale*vec3(sqrt(2.0f / 9.0f), sqrt(2.0f / 3.0f), -(1.0f/3.0f));
    //Left back
	vec3 corner3 = inV + scale*vec3(sqrt(2.0f / 9.0f), -1.0* sqrt(2.0f / 3.0f), -(1.0f/3.0f));
    vec3 top = inV + scale*vec3(0.0f, 0.0f, 1.0f);

    //Adding triangles to scene
    //Back
    scene.push_back(Triangle(top, corner2, corner3, incolor, reflType));
    //Bottom
    scene.push_back(Triangle(corner1, corner3, corner2, incolor, reflType));
    //Front right
    scene.push_back(Triangle(top, corner1, corner2, incolor, reflType));
    //Front left
    scene.push_back(Triangle(top, corner3, corner1,  incolor, reflType));

    std::cout << "Added a tetrahedron to the scene!" << std::endl << std::endl;
}

void Scene::addSphere(vec3 inCenter, float radius, vec3 inColor, int inReflType, float inRoughness) {
    spheres.push_back(Sphere(inCenter, radius, inColor, inReflType, inRoughness));
    
    std::cout << "Added a sphere with center: " << glm::to_string(inCenter) << "color: " << glm::to_string(inColor) << "radius: " << radius << " to the scene!" << std::endl << std::endl;
}

void Scene::addAreaLight(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
    lights.push_back(Triangle(v0, v2, v1, vec3(1.0f), 3));
    lights.push_back(Triangle(v0, v3, v2, vec3(1.0f), 3));
    scene.push_back(Triangle(v0, v2, v1, vec3(1.0f), 3));
    scene.push_back(Triangle(v0, v3, v2, vec3(1.0f), 3));
}

//u & v is between 0 and 1
glm::vec3 Scene::getPointOnAreaLight(float u, float v)
{
    glm::vec3 v1 = lights[0].v0 - lights[0].v1;
    glm::vec3 v2 = lights[1].v2 - lights[0].v1;
    return lights[0].v0 + u * v1 + v * v2;
}

vec3* Scene::findIntersection(Ray &arg) {
        
    for(int i = 0; i < (int)scene.size(); i++) {
        scene[i].rayIntersection(arg);
    }
    for(int i = 0; i < (int)spheres.size(); i++) {
        spheres[i].rayIntersection(arg);
    }
    arg.sortIntersections();
    
    //Choose closest intersection
    if(arg.intSectPoints.size() > 0) {
        arg.intSectPoint = &arg.intSectPoints[0].interSectPoint;
        if(arg.intSectPoints[0].tri != nullptr ) {
            arg.endTri = arg.intSectPoints[0].tri;
        }
        else {
            arg.endSphere = arg.intSectPoints[0].sphere;
        }
    }
    return arg.intSectPoint;
}

void Scene::addPointLight(vec3 inCenter) {
    pointLights.push_back(PointLight(inCenter));
    
    std::cout << "Added a pointlight with center: " << glm::to_string(inCenter) << "to the scene!" << std::endl << std::endl;
}

bool Scene::isInShadow(Ray &theRay) {
    
    findIntersection(theRay);
    
    //Check if an object is intersecting ray to light
    for(int i = 0; i < theRay.intSectPoints.size(); i++) {
        //Check so distance to light is greater than distance to intersecting object
        float distToLight = glm::length(*theRay.end - *theRay.start);
        float distToIntersection = glm::length(theRay.intSectPoints[i].interSectPoint - *theRay.start); //Ugly solution
        
        int material = theRay.intSectPoints[i].tri ? theRay.intSectPoints[i].tri->surf.reflectionType : theRay.intSectPoints[i].sphere->surf.reflectionType;
        
        if( material != 2 && distToIntersection < distToLight ){
            return true;
        }
    }
    
    return false;
}

//Whitted ray-tracing & monte carlo
vec3 Scene::traceRay(Ray* arg, int iteration) {

    //Check for when rays go inbetween triangles
    if(arg == nullptr || arg->start == nullptr || arg->end == nullptr) {
        return vec3(0.0f, 0.0f, 0.0f);
    }
    
    //Add intersections to ray
    findIntersection(*arg);
    
    //No intersections found
    if(arg->intSectPoint == nullptr) {
        return vec3(0.0f,0.0f,1.0f);
    }
    if(iteration > 20) {
        return vec3(1.0f,0.0f,0.0f);
    }
    
    vec3 diffuse = vec3(0.0f);
    
    //Diffuse surface, monte carlo ray tracing
    if((arg->endTri && arg->endTri->surf.reflectionType == 0) ||
      (arg->endSphere && arg->endSphere->surf.reflectionType == 0)) {
        
        //Monte carlo ray
        arg->monteCarloRay = traceRayMonteCarlo(arg);
        
        vec3 normal = normalize(arg->endTri ? arg->endTri->normal : arg->endSphere->calcNormal(*arg));
        
        float u = 0.0f;
        float v = 0.0f;
        int N_samples = 16;
        //If intersection point is not in shadow, set it to BRDF
        for(int i = 0; i < N_samples; i++) {
            u = (*dis)(*gen);
            v = (*dis)(*gen);
            
            Ray shadowRay = Ray(arg->intSectPoint, new vec3(getPointOnAreaLight(u, v)));
            vec3 direction = normalize(*shadowRay.end - *shadowRay.start);
            
            float cos_theta = glm::dot(direction, normal);
            float cos_light_angle = glm::dot(normal, -1.0f*normalize(*shadowRay.end - *shadowRay.start));
           float light_solid_angle = 4.0f / N_samples * glm::clamp(cos_light_angle, 0.0f, 1.0f) / glm::pow(glm::length(direction), 2) / (M_PI * 2);

            if(!isInShadow(shadowRay)) {
                diffuse += cos_theta * getLambertianBRDF(*arg) * cos_light_angle * light_solid_angle;
            }
        }
        // Russian roulette, random termination of rays
//        float random = (*dis)(*gen);
//        float absorpionProbability = 0.15f;
//        float nonTerminationProbability = iteration == 0 ? 1.0 : 1.0f - absorpionProbability;
//        if (random > nonTerminationProbability || iteration > 20)
//            return vec3(0.0f);
        
        //Recurse
        diffuse += traceRay(arg->monteCarloRay, iteration + 1);
    }
    //Perfectly reflective surface
    else if((arg->endSphere && arg->endSphere->surf.reflectionType == 1) ||
            (arg->endTri && arg->endTri->surf.reflectionType == 1)) {
        
        //Perfectly reflected ray
        arg->reflectedRay = traceRayPerfectReflection(*arg);
        //Recurse
        diffuse = traceRay(arg->reflectedRay, iteration + 1);
    }
    //Perfectly transparent surface
    else if((arg->endSphere && arg->endSphere->surf.reflectionType == 2) ||
    (arg->endTri && arg->endTri->surf.reflectionType == 2)) {
        
        float fresnelCoeff = traceRayRefraction(arg);
        arg->reflectedRay = traceRayPerfectReflection(*arg);

        //Brewster angle - reflection is total
        if(!arg->refractedRay) {
            fresnelCoeff = 1.0f;
        }
        diffuse = (1.0f-fresnelCoeff)*traceRay(arg->refractedRay, iteration + 1) + fresnelCoeff * traceRay(arg->reflectedRay, iteration + 1);
    }
    //Emissive surface
    else if((arg->endSphere && arg->endSphere->surf.reflectionType == 3) ||
            (arg->endTri && arg->endTri->surf.reflectionType == 3)) {
        diffuse = vec3(1.0f);
    }
    
    return diffuse;
}

float Scene::traceRayRefraction(Ray *arg){
    
    vec3 N = normalize(arg->endTri ? arg->endTri->normal : arg->endSphere->calcNormal(*arg));
    //Incoming ray
    vec3 I = normalize(vec3(*arg->end - *arg->start));
    vec3 R = vec3(0.0f);
    
    float n1 = 1.0f;
    float n2 = 1.53f;
    
    //If the ray is inside an object
    if(dot(N, I) > 0.0f) {
        N = -1.0f*N;
        n1 = 1.53f;
        n2 = 1.0f;
    }
    float eta = n1/n2;
    
    //Fresnels approximation to Schlicks equation
    float R_0 = pow((n1 - n2)/(n1 + n2), 2);
    float fresnelCoeff = R_0 + (1 - R_0) * pow(1 - glm::dot(N, -1.0f*I),5);
    
    //vec3 refractionGLM = glm::refract(dir, normal, eta);
    float k = 1.0f - eta * eta * (1.0f - dot(N, I) * dot(N, I));
    if (k > 0.0)
        R = eta * I - (eta * dot(N, I) + sqrt(k)) * N;

    //Check for brewster angle
    if (R != vec3(0.0f)) {
        vec3* endRefr = new vec3(*arg->intSectPoint + R);
        vec3* startRefr = new vec3(*arg->intSectPoint);
        
        arg->refractedRay = new Ray(startRefr, endRefr);
    }

    return fresnelCoeff;
}

Ray* Scene::traceRayMonteCarlo(Ray *arg) {

    //Setting up the estimator by generating 2 random numbers [0,1]
    float randX = (*dis)(*gen);
    float randY = (*dis)(*gen);
    float PI = 3.14f;
    
    //Monte Carlo solution with a cosine estimator
    float azimuth = 2.0f*PI*randX;
    float inclination = glm::asin(glm::sqrt(randY));

    vec3 I = normalize(*arg->end - *arg->start);
    vec3 z = normalize(arg->endTri ? arg->endTri->normal : arg->endSphere->calcNormal(*arg));
    vec3 x = normalize(I - dot(I, z) * z);
    
    //Transform to local coordinate system
    glm::vec3 y = glm::normalize(glm::cross(z, -x));
    //Create outgoing direction
    glm::vec3 outDirGlobal = z;
    
    //Rotate in random direction
    outDirGlobal = glm::normalize(glm::rotate(outDirGlobal, inclination, y));
    outDirGlobal = glm::normalize(glm::rotate(outDirGlobal, azimuth, z));

    //Add new ray to the tree
    vec3* endvec3 = new vec3(*arg->intSectPoint + outDirGlobal);
    Ray *outRay = new Ray(arg->intSectPoint, endvec3);

    return outRay;
}

Ray* Scene::traceRayPerfectReflection(Ray &inRay) {
    vec3 I = normalize(*inRay.end - *inRay.start);
    vec3 normal = normalize(inRay.endTri ? (inRay.endTri->normal) : (inRay.endSphere->calcNormal(inRay)));
    vec3 outDir = (I - 2.0f*(dot(I,normal)*normal));
    //Offset
    vec3 *start = new vec3(*inRay.intSectPoint + normal*0.01f);
    Ray* outRay = new Ray(start, new vec3(*inRay.intSectPoint + outDir));
    
    return outRay;
}

vec3 Scene::getLambertianBRDF(Ray &endRay) {
    
    vec3 albedo = endRay.endTri ? endRay.endTri->color : endRay.endSphere->color;
    return albedo / (float)M_PI;
    //If the ray hits a triangle or sphere
//    vec3 normal = normalize(endRay.endTri ? endRay.endTri->normal : endRay.endSphere->calcNormal(endRay));
//    vec3 albedo = endRay.endTri ? endRay.endTri->color : endRay.endSphere->color;
//
//    //Add shading to objects that are hit by light
//    vec3 rayToLight = normalize(pointLights[0].pos - *endRay.intSectPoint);
//    float alpha = dot(normal, rayToLight);
//
//    if ( alpha > 0.0f ) {
//        return albedo * alpha;
//    }
//    else {
//        return vec3(0.0f,0.0f,0.0f);
//    }
}

vec3 Scene::getOrenNayarBRDF(Ray &endRay) {
    
    //Get normal of triangle or sphere
    vec3 normal = endRay.endTri ? endRay.endTri->normal : endRay.endSphere->calcNormal(endRay);
    //Get surface color of triangle or sphere
    vec3 albedo = endRay.endTri ? endRay.endTri->surf.color : endRay.endSphere->surf.color;
    //Get surface color of triangle or sphere
    float roughness = endRay.endTri ? endRay.endTri->surf.roughness : endRay.endSphere->surf.roughness;
    
   float sigma2 = roughness * roughness;
        
    vec3 inDir = normalize(*endRay.start - *endRay.intSectPoint);
    vec3 lightDir = normalize(pointLights[0].pos - *endRay.intSectPoint);
    vec3 outDir = normalize(*endRay.monteCarloRay->end - *endRay.intSectPoint);

    float A = 1 - 0.5 * sigma2 / (sigma2 + 0.57);
    float B = 0.45 * sigma2 / (sigma2 + 0.09);
    float cos_theta_d1 = glm::dot(inDir, normal);
    float cos_theta_d2 = glm::dot(lightDir, normal);
    float theta = glm::acos(cos_theta_d2);
    float theta_d1 = glm::acos(cos_theta_d1);
    float alpha = glm::max(theta, theta_d1);
    float beta = glm::min(theta, theta_d1);
    float cos_d1_d2 = glm::dot(inDir, lightDir);

    return albedo / 3.14f * cos_theta_d2 * 
    (A + (B * glm::max(0.0f, cos_d1_d2)) * glm::sin(alpha) * glm::tan(beta));
    
    
   /*
    float A = 1.0f - (0.5f * sigma2/2.0f*(sigma2 + 0.33f));
    float B = 0.45f * sigma2/(sigma2+ 0.09f);
    
    //float L = max(0.0, dotProduct(normal, lightDir));
    //float V = max(0.0, dotProduct(normal, inDir));
    //float P = max(0.0, dotProduct(lightDir-normal*L, inDir-normal*V));
    
    //vec3 Lr = albedo  * ( A + B * P * sqrt((1-L*L)*(1-V*V))/max(L,V));
    
    
    float cos_thetaR = dot(inDir, normal);
    float cos_thetaI = dot(lightDir, normal);
    
    float cos_phiI = dot(normalize(lightDir - normal), normalize(inDir - normal));
    
    float thetaR = glm::acos(cos_thetaR);
    float thetaI = glm::acos(cos_thetaI);
    float alphaAngle = std::max(thetaR, thetaI);
    float betaAngle = std::min(thetaR, thetaI);
       
    vec3 Lr =  albedo * ( A + (B * glm::max(0.0f, cos_phiI) * glm::sin(alphaAngle) * glm::tan(betaAngle)));

    return Lr;*/
   
}

