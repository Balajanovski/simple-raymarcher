// 
// Created by Balajanovski on 21/12/2017.
//

#include "Intersection.h"

Intersection min(const Intersection& a, const Intersection& b) {
    return (a.distance() < b.distance()) ? a : b;
}

Intersection max(const Intersection& a, const Intersection& b) {
    return (a.distance() > b.distance()) ? a : b;
}