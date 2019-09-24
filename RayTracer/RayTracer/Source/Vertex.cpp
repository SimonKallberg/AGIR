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
Vertex operator-(Vertex lhs, Vertex rhs) {
    return Vertex(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

std::ostream& operator<<(std::ostream& out, const Vertex& v1) {
	out << "(" << v1.x << "," << v1.y << "," << v1.z << ")" << std::endl;
	return out;
}