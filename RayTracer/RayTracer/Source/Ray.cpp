//
//  Ray.cpp
//  AGIR
//
//  Created by Ylva Selling on 2019-09-19.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#include "Ray.hpp"


std::ostream& operator<<(std::ostream& out, const Ray& v1) {
	out << *v1.start << " " << *v1.end << std::endl;
	return out;
}