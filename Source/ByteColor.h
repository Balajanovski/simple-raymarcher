// 
// Created by Balajanovski on 29/12/2017.
//

#ifndef SIMPLE_RAYTRACER_RGB_H
#define SIMPLE_RAYTRACER_RGB_H

// This structure is used by ImageBuffer as a substitute for
// the floating point based Color class, due to libPNG only
// supporting a byte based ByteColor color format

struct ByteColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif //SIMPLE_RAYTRACER_RGB_H
