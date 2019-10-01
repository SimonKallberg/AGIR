//
//  Vector3.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-30.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Vector3.hpp"

double Vector3::length() {
    return sqrt((x*x) + (y*y) + (z*z));
}

void Vector3::normalize() {
    double lengthVec = length();
    x = x/lengthVec;
    y = y/lengthVec;
    z = z/lengthVec;
}

std::ostream& operator<<(std::ostream& out, const Vector3& v1) {
    out << "(" << v1.x << ", " << v1.y << ", " << v1.z << ")" << std::endl;
    return out;
}

Vector3 operator+(Vector3 lhs, Vector3 rhs) {
    return Vector3(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}

Vector3 operator-(Vector3 lhs, Vector3 rhs) {
    return Vector3(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}
Vector3 operator*(double lhs, Vector3 rhs) {
    return Vector3(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z);
}

Vector3 operator*(Vector3 lhs, double rhs) {
    return Vector3(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs);
}
Vector3 operator/(Vector3 lhs, double rhs) {
    return Vector3(lhs.x/rhs, lhs.y/rhs, lhs.z/rhs);
}

Vector3 crossProduct(Vector3 vector1, Vector3 vector2) {
    return Vector3((vector1.y*vector2.z)-(vector1.z*vector2.y),
                     -((vector1.x*vector2.z)-(vector1.z*vector2.x)),
                     (vector1.x*vector2.y)-(vector1.y*vector2.x));
}

double dotProduct(Vector3 lhs, Vector3 rhs) {
    return (lhs.x*rhs.x)+(lhs.y*rhs.y)+(lhs.z*rhs.z);
}

bool operator<(Vector3 lhs, double rhs) {
    if (lhs.x < rhs && lhs.y < rhs && lhs.z < rhs) {
        return true;
    }
    else return false;
}
bool operator>(Vector3 lhs, double rhs) {
    if (lhs.x > rhs && lhs.y > rhs && lhs.z > rhs) {
        return true;
    }
    else return false;
}
