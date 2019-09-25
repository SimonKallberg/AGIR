//
//  Vertex.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Vertex.hpp"

Vertex operator+(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}
Vertex operator*(double lhs, Vertex rhs) {
    return Vertex(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z);
}
Vertex operator*(Vertex lhs, double rhs) {
    return Vertex(rhs*lhs.x, rhs*lhs.y, rhs*lhs.z);
}
Vertex operator-(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}
bool operator<(Vertex lhs, double rhs) {
    if (lhs.x < rhs && lhs.y < rhs && lhs.z < rhs) {
        return true;
    }
    else return false;
}
bool operator>(Vertex lhs, double rhs) {
    if (lhs.x > rhs && lhs.y > rhs && lhs.z > rhs) {
        return true;
    }
    else return false;
}

std::ostream& operator<<(std::ostream& out, const Vertex& v1) {
	out << "(" << v1.x << "," << v1.y << "," << v1.z << ")" << std::endl;
	return out;
}
