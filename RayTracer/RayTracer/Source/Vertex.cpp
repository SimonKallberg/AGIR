//
//  Vertex.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Vertex.hpp"

Vertex operator+(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.vec3+rhs.vec3);
}
Vertex operator*(double lhs, Vertex rhs) {
    return Vertex(lhs*rhs.vec3);
}
Vertex operator*(Vertex lhs, double rhs) {
    return Vertex(lhs.vec3*rhs);
}
Vertex operator-(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.vec3-rhs.vec3);
}
bool operator<(Vertex lhs, double rhs) {
    if (lhs.vec3 < rhs) {
        return true;
    }
    else return false;
}
bool operator>(Vertex lhs, double rhs) {
    if (lhs.vec3 > rhs) {
        return true;
    }
    else return false;
}

std::ostream& operator<<(std::ostream& out, const Vertex& v1) {
	out << v1.vec3;
	return out;
}
