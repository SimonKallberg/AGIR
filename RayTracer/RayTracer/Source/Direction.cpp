//
//  Direction.cpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#include "Direction.hpp"

std::ostream& operator<<(std::ostream& out, const Direction& v1) {
	out << v1.x << " " << v1.y << " " << v1.z << std::endl;
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

double dotProduct(Direction lhs, Direction rhs) {
    return (lhs.x*rhs.x)+(lhs.y*rhs.y)+(lhs.z*rhs.z);
}
