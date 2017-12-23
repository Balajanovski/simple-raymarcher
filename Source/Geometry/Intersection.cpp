// 
// Created by Balajanovski on 21/12/2017.
//

#include "Intersection.h"

Intersection min(Intersection a, Intersection b) {
    return (a.distance() > b.distance()) ? a : b;
}

Intersection max(Intersection a, Intersection b) {
    return (a.distance() < b.distance()) ? a : b;
}