//
//  Vector3.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>

class Vector3 {
    
public:
    double x, y, z;
    
    Vector3(double inX = 0.0, double inY = 0.0, double inZ = 0.0)
        : x(inX), y(inY), z(inZ)  {}
    
    double length();
    void normalize();
    friend Vector3 crossProduct(Vector3 vector1, Vector3 vector2);
    friend Vector3 operator+(Vector3 lhs, Vector3 rhs);
    friend Vector3 operator-(Vector3 lhs, Vector3 rhs);
    friend Vector3 operator*(double lhs, Vector3 rhs);
    friend Vector3 operator*(Vector3 lhs, double rhs);
    friend Vector3 operator/(Vector3 lhs, double rhs);
    friend bool operator<(Vector3 lhs, double rhs);
    friend bool operator>(Vector3 lhs, double rhs);
    friend double dotProduct(Vector3 lhs, Vector3 rhs);
    friend std::ostream& operator<<(std::ostream& out, const Vector3& v1);
};

#endif /* Vector3_hpp */
