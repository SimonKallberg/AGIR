//
//  Direction.hpp
//  
//
//  Created by Ylva Selling on 2019-09-20.
//

#ifndef Direction_hpp
#define Direction_hpp

#include <stdio.h>
#include <iostream>
#include "Vertex.hpp"

class Direction {
public:
	double x, y, z;

	Direction(double inX, double inY, double inZ)
		: x(inX), y(inY), z(inZ) {}
	//Conversion from vertex to direction
	Direction(Vertex v)
		: x(v.x), y(v.y), z(v.z) {}

	friend Direction crossProduct(Direction vector1, Direction vector2);
	friend Direction operator+(Direction lhs, Direction rhs);
	friend Direction operator-(Direction lhs, Direction rhs);
	friend double dotProduct(Direction lhs, Direction rhs);
	friend std::ostream& operator<<(std::ostream& out, const Direction& v1);
};

#endif
