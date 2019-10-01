//
//  PointLight.hpp
//  AGIR
//
//  Created by Ylva Selling on 2019-10-01.
//  Copyright © 2019 Ylva Selling. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <stdio.h>
#include "Vertex.hpp"

class PointLight {
public:
    PointLight(Vertex inC = Vertex(1.0, 1.0, 0.0))
      : pos(inC) { }

    Vertex pos = Vertex(Vector3(0.0,0.0,0.0));
};


#endif /* PointLight_hpp */
