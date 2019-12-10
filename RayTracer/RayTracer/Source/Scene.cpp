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
    
    //Polymorphism
    //Setting up a room shaped as a polygon
    // Wall 1 - yellow
    geometry.push_back(new Triangle(vec3(-3.0f, 0.0f, 5.0f), vec3(0.0f, 6.0f, 5.0f), vec3(-3.0f, 0.0f, -5.0f), vec3(0.36f, 0.45f, 0.63f)));
    geometry.push_back(new Triangle(vec3(0.0f, 6.0f, 5.0f), vec3(0.0f, 6.0f, -5.0f), vec3(-3.0f, 0.0f, -5.0f), vec3(1.0f, 1.0f, 0.0f)));
    
    //Wall2 - matte light pink
    geometry.push_back(new Triangle(vec3(0.0f, 6.0f, 5.0f),vec3(10.0f, 6.0f, 5.0f), vec3(0.0f, 6.0f ,-5.0f), vec3(0.23f, 0.31f, 0.27f)));
    geometry.push_back(new Triangle(vec3(10.0f, 6.0f, 5.0f),vec3(10.0f, 6.0f , -5.0f),vec3(0.0f, 6.0f ,-5.0f),vec3(0.94f, 0.66f, 0.73f)));
    
    //Wall 3 - matte blue
    geometry.push_back(new Triangle(vec3(10.0f, 6.0f, 5.0f), vec3(13.0f, 0.0f, 5.0f), vec3(10.0f, 6.0f, -5.0f), vec3(1.0f, 1.0f, 0.0f)));
    geometry.push_back(new Triangle(vec3(13.0f, 0.0f, 5.0f), vec3(13.0f, 0.0f, -5.0f), vec3(10.0f, 6.0f, -5.0f), vec3(0.36f, 0.45f, 0.63f)));
    
    //Wall 4 - dark matte pink
    geometry.push_back(new Triangle(vec3(-3.0f, 0.0f, -5.0f), vec3(0.0f, -6.0f, 5.0f), vec3(-3.0f, 0.0f, 5.0f), vec3(0.92f, 0.64f, 0.59f)));
    geometry.push_back(new Triangle(vec3(-3.0f, 0.0f, -5.0f), vec3(0.0f, -6.0f, -5.0f), vec3(0.0f, -6.0f, 5.0f), vec3(0.76f, 0.4f, 0.5f)));

    //Wall 5 - dark green
    geometry.push_back(new Triangle(vec3(0.0f,-6.0f,-5.0f), vec3(10.0f,-6.0f,5.0f), vec3(0.0f,-6.0f,5.0f), vec3(0.94f, 0.66f, 0.73f)));
    geometry.push_back(new Triangle(vec3(0.0f,-6.0f,-5.0f), vec3(10.0f,-6.0f,-5.0f), vec3(10.0f,-6.0f,5.0f), vec3(0.23f, 0.31f, 0.27f)));
    
    //Wall 6 - green
    geometry.push_back(new Triangle(vec3(10.0f,-6.0f,-5.0f), vec3(13.0f,0.0f,5.0f), vec3(10.0f,-6.0f,5.0f), vec3(0.76f, 0.4f, 0.5f)));
    geometry.push_back(new Triangle(vec3(10.0f,-6.0f,-5.0f), vec3(13.0f,0.0f,-5.0f), vec3(13.0f,0.0f,5.0f), vec3(0.92f, 0.64f, 0.59f)));
    
    //celing - white
    geometry.push_back(new Triangle(vec3(0.0f, -6.0f, 5.0f), vec3(0.0f,6.0f,5.0f), vec3(-3.0f, 0.0f, 5.0f), vec3(1.0f, 1.0f, 1.0f)));
    geometry.push_back(new Triangle(vec3(0.0f,-6.0f,5.0f), vec3(10.0f,6.0f,5.0f), vec3(0.0f,6.0f,5.0f), vec3(1.0f, 1.0f, 1.0f)));
    geometry.push_back(new Triangle(vec3(0.0f, -6.0f, 5.0f), vec3(10.0f,-6.0f,5.0f), vec3(10.0f, 6.0f, 5.0f), vec3(1.0f, 1.0f, 1.0f)));
    geometry.push_back(new Triangle(vec3(10.0f,-6.0f,5.0f), vec3(13.0f,0.0f,5.0f), vec3(10.0f,6.0f,5.0f), vec3(1.0f, 1.0f, 1.0f)));
    
    //floor - white
    geometry.push_back(new Triangle(vec3(-3.0f,0.0f,-5.0f), vec3(0.0f,6.0f,-5.0f), vec3(0.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    geometry.push_back(new Triangle(vec3(0.0f,6.0f,-5.0f), vec3(10.0f,6.0f,-5.0f), vec3(0.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    geometry.push_back(new Triangle(vec3(10.0f,6.0f,-5.0f), vec3(10.0f,-6.0f,-5.0f), vec3(0.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
    geometry.push_back(new Triangle(vec3(10.0f,6.0f,-5.0f), vec3(13.0f,0.0f,-5.0f), vec3(10.0f,-6.0f,-5.0f), vec3(1.0f, 1.0f, 1.0f)));
}

void Scene::addTetrahedron(vec3 inV, float scale, vec3 incolor, Material reflType, float inRoughness) {
	
    //Closest to camera
	vec3 corner1 = inV + scale*vec3(-sqrt(8.0f/9.0f), 0.0, -(1.0f/3.0f));
    //Right back
	vec3 corner2 = inV + scale*vec3(sqrt(2.0f / 9.0f), sqrt(2.0f / 3.0f), -(1.0f/3.0f));
    //Left back
	vec3 corner3 = inV + scale*vec3(sqrt(2.0f / 9.0f), -1.0* sqrt(2.0f / 3.0f), -(1.0f/3.0f));
    vec3 top = inV + scale*vec3(0.0f, 0.0f, 1.0f);

    //Polymorphism
    //Adding triangles to scene
    //Back
    geometry.push_back(new Triangle(top, corner2, corner3, incolor, reflType));
    //Bottom
    geometry.push_back(new Triangle(corner1, corner3, corner2, incolor, reflType));
    //Front right
    geometry.push_back(new Triangle(top, corner1, corner2, incolor, reflType));
    //Front left
    geometry.push_back(new Triangle(top, corner3, corner1,  incolor, reflType));

    std::cout << "Added a tetrahedron to the scene!" << std::endl << std::endl;
}

void Scene::addSphere(vec3 inCenter, float radius, vec3 inColor, Material inReflType, float inRoughness) {
    
    //Polymorphism
    geometry.push_back(new Sphere(inCenter, radius, inColor, inReflType, inRoughness));
    
    std::cout << "Added a sphere with center: " << glm::to_string(inCenter) << ", color: " << glm::to_string(inColor) << ", radius: " << radius << " to the scene!" << std::endl << std::endl;
}

void Scene::addPointLight(vec3 inCenter) {
    pointLights.push_back(PointLight(inCenter));
    
    std::cout << "Added a pointlight with center: " << glm::to_string(inCenter) << "to the scene!" << std::endl << std::endl;
}

void Scene::addAreaLight(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
    lights.push_back(Triangle(v0, v2, v1, vec3(1.0f), EMISSIVE));
    lights.push_back(Triangle(v0, v3, v2, vec3(1.0f), EMISSIVE));
    std::cout << "Added an area light! " << endl;
}

//u & v is between 0 and 1
glm::vec3 Scene::getPointOnAreaLight(float u, float v)
{
    glm::vec3 v1 = lights[0].v2 - lights[0].v0;
    glm::vec3 v2 = lights[1].v1 - lights[1].v0; //OK
    return lights[0].v0 + u * v1 + v * v2;
}

vec3* Scene::findIntersection(Ray &ray) {
    
    for(int i = 0; i < (int)geometry.size(); i++) {
        geometry[i]->rayIntersection(ray);
    }
    ray.sortIntersections();
    
    //Choose closest intersection by sorting vector of intersections
    if(ray.intSectPoints.size() > 0) {
        ray.intSectPoint = &ray.intSectPoints[0].interSectPoint;
        ray.endObject = ray.intSectPoints[0].object;
        ray.objectNormal = ray.intSectPoints[0].normal;
    }
    return ray.intSectPoint;
}

bool Scene::pointInShadow(vec3 &surfPoint, vec3 &lightPoint) {
    
    Ray rayToLight = Ray(&surfPoint, &lightPoint);
    findIntersection(rayToLight);
    
    //Check if an object is intersecting ray to light
    if(rayToLight.intSectPoints.size() > 0) {
        //Check so distance to light is greater than distance to intersecting object
        float distToLight = glm::length(*rayToLight.end - *rayToLight.start);
        float distToIntersection = glm::length(rayToLight.intSectPoints[0].interSectPoint - *rayToLight.start); //Ugly solution
        Material material = rayToLight.endObject->material();
        
        //No shadow for transparent objects
        if(material != TRANSPARENT && distToIntersection < distToLight ){
            return true;
        }
    }
    return false;
}

//Whitted ray-tracing & monte carlo
vec3 Scene::traceRay(Ray* ray, int iteration) {

    //Check for when rays go inbetween triangles
    if(ray == nullptr || ray->start == nullptr || ray->end == nullptr) {
        return vec3(0.0f, 0.0f, 0.0f);
    }
    
    //Add intersections to ray
    findIntersection(*ray);
    
    //No intersections found, ray goes between triangles. Return black.
    if(ray->intSectPoint == nullptr || ray->endObject == nullptr) {
        return vec3(0.0f,0.0f,0.0f);
    }
    
    if( iteration > 20) {
        return vec3(1.0f,0.0f,0.0f);
    }
    
    vec3 diffuse = vec3(0.0f);
    
    switch(ray->endObject->material()) {
    //Diffuse surface, monte carlo ray tracing
        case LAMBERTIAN:
        case OREN_NAYAR: {

            //Monte carlo ray
            ray->diffuseRay = traceRayMonteCarlo(ray);
            
            vec3 normal = ray->objectNormal;
            int samples = 16; //Samples of area light
           
            //Sample area light w "samples" no of random points on area light
            for(int i = 0; i < samples; i++) {
                
               float u = (*dis)(*gen);
               float v = (*dis)(*gen);
               
               vec3 light = getPointOnAreaLight(u, v);
                
               //If point is illuminated, add BRDF, else color is black
               if (!pointInShadow(*ray->intSectPoint, light)) {
                   vec3 rayToLight = normalize(light - *ray->intSectPoint);
                   float cos_theta = dot(normal, rayToLight);
                   cos_theta = std::max(cos_theta, 0.0f);
                   
                   diffuse += cos_theta * getOrenNayarSurfaceColor(*ray, light);
               }
            }
            
            //Average color on no of samples of area light
            diffuse = diffuse /(float)samples;
            
            // Russian roulette, random termination of rays
            float random = (*dis)(*gen);
            float absorpionProbability = 1.0f;
            float nonTerminationProbability = 1.0f - absorpionProbability;
            if (random > nonTerminationProbability || iteration > 10) {
                return diffuse;
            }
            //Recurse
            diffuse += 0.8f*traceRay(ray->diffuseRay, iteration + 1);
            break;
        }
        //Perfectly reflective surface
        case REFLECTIVE: {
            //Perfectly reflected ray
            ray->reflectedRay = traceRayPerfectReflection(*ray);
            //Recurse
            diffuse = traceRay(ray->reflectedRay, iteration + 1);
            break;
        }
    //Perfectly transparent surface
    case TRANSPARENT: {
    
        float fresnelCoeff = traceRayRefraction(ray);
        ray->reflectedRay = traceRayPerfectReflection(*ray);

        //Brewster angle - reflection is total
        if(!ray->refractedRay) {
            fresnelCoeff = 1.0f;
        }
        //Recurse
        diffuse = (1.0f-fresnelCoeff) * traceRay(ray->refractedRay, iteration + 1) + fresnelCoeff * traceRay(ray->reflectedRay, iteration + 1);
        break;
    }
    case EMISSIVE: {
        return vec3(1.0f);
        break;
        }
    }
    return diffuse;
}

float Scene::traceRayRefraction(Ray *ray){
    
    //Normal
    vec3 N = ray->objectNormal;
    //Incoming ray
    vec3 I = normalize(vec3(*ray->end - *ray->start));
    //Refracted ray
    vec3 R = vec3(0.0f);
    
    //Refraction indexes: n1 is first medium, n2 is second
    float n1 = 1.0f;
    float n2 = 1.53f;
    
    //Check the ray is inside an object
    if(dot(N, I) > 0.0f) {
        N = -1.0f*N;
        n1 = 1.53f;
        n2 = 1.0f;
    }
    float eta = n1/n2;
    
    //Fresnels approximation to schlicks equation
    float R_0 = pow((n1 - n2)/(n1 + n2), 2);
    float fresnelCoeff = R_0 + (1 - R_0) * pow(1 - glm::dot(N, -1.0f*I),5);
    
    float k = 1.0f - eta * eta * (1.0f - dot(N, I) * dot(N, I));
    if (k > 0.0)
        R = eta * I - (eta * dot(N, I) + sqrt(k)) * N;

    //Check for brewster angle
    if (R != vec3(0.0f)) {
        vec3* endRefr = new vec3(*ray->intSectPoint + R);
        vec3* startRefr = new vec3(*ray->intSectPoint);
        
        ray->refractedRay = new Ray(startRefr, endRefr);
    }

    return fresnelCoeff;
}

Ray* Scene::traceRayMonteCarlo(Ray *ray) {

    //Setting up the estimator by generating 2 random numbers [0,1]
    float randX = (*dis)(*gen);
    float randY = (*dis)(*gen);
    
    //Monte Carlo solution with a cosine estimator
    float azimuth = 2.0f * M_PI * randX;
    float inclination = glm::asin(glm::sqrt(randY));

    //Incoming ray
    vec3 I = normalize(*ray->end - *ray->start);
    
    //Create local coordinate system from incoming ray and surface normal
    vec3 z = ray->objectNormal;
    vec3 x = normalize(I - dot(I, z) * z);
    glm::vec3 y = glm::normalize(glm::cross(z, -x));
    
    //Create outgoing direction
    glm::vec3 outDirGlobal = z;
    
    //Rotate in random direction
    outDirGlobal = glm::normalize(glm::rotate(outDirGlobal, inclination, y));
    outDirGlobal = glm::normalize(glm::rotate(outDirGlobal, azimuth, z));

    //Outgoing ray
    vec3* end = new vec3(*ray->intSectPoint + outDirGlobal);
    Ray *outRay = new Ray(ray->intSectPoint, end);

    return outRay;
}

Ray* Scene::traceRayPerfectReflection(Ray &ray) {
    vec3 I = normalize(*ray.end - *ray.start);
    vec3 normal = ray.objectNormal;
    vec3 outDir = (I - 2.0f*(dot(I,normal)*normal));
    //Offset
    vec3 *start = new vec3(*ray.intSectPoint + normal*0.01f);
    Ray* outRay = new Ray(start, new vec3(*ray.intSectPoint + outDir));
    
    return outRay;
}

vec3 Scene::getLambertianSurfaceColor(Ray &ray) {
    
    //Get color of the surface the ray hits
    vec3 albedo = ray.endObject->color();
    return albedo/((float)M_PI);
}

vec3 Scene::getOrenNayarSurfaceColor(Ray &ray, vec3 &lightPoint) {
    
    //Get normal of intersecting object
    vec3 normal = ray.objectNormal;
    //Get surface color intersecting object
    vec3 albedo = ray.endObject->color();
    //Get surface roughness of triangle or sphere
    float roughness = ray.endObject->roughness();
    float sigma2 = roughness * roughness;

    vec3 inDir = normalize(*ray.start - *ray.intSectPoint);
    vec3 lightDir = normalize(lightPoint - *ray.intSectPoint);
    
    //Calculate angles
    float theta_view =  acos(dot(inDir, normal));
    float theta_light = acos(dot(lightDir, normal));
    vec3 ortogonalToNormal = normalize(inDir - dot(inDir, normal) * normal);
    float phi_view = acos(dot(inDir, ortogonalToNormal));
    float phi_light = acos(dot(lightDir, ortogonalToNormal));

    //Variables used in Oren Nayar formula
    float A = 1 - 0.5 * sigma2 / (sigma2 + 0.33); //kbladin 0.57
    float B = 0.45 * sigma2 / (sigma2 + 0.09);
    float alpha = glm::max(theta_light, theta_view);
    float beta = glm::min(theta_light, theta_view);

    //Oren Nayar equation
    return albedo / (float)M_PI * (A + (B * glm::max(0.0f, cos(phi_light - phi_view))) * glm::sin(alpha) * glm::tan(beta));
}

