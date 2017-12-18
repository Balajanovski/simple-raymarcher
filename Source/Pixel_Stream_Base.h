// 
// Created by Balajanovski on 15/12/2017.
//

#ifndef SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H
#define SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H

#include <vector>

#include "Color.h"
#include "Screen.h"

class Pixel_Stream_Base {
    friend class Pixel_Calculator;
    // Stores the pixel data
    std::vector<Color> m_buffer;
protected:
    std::vector<Color> &get_buffer() {
        return m_buffer;
    }

    // Iterator to where in the buffer the appending is happening
    typename std::vector<Color>::iterator pos_iter;

    // Represents the size of the m_window to which the buffer is writing
    std::shared_ptr<Screen<int>> bounds;
public:
    Pixel_Stream_Base(std::shared_ptr<Screen<int>> &bnd) :
            m_buffer(bnd->size()), bounds(bnd) { pos_iter = m_buffer.begin(); }
    virtual ~Pixel_Stream_Base() { };
    virtual void flush() = 0;
    virtual void clear() = 0;

    Pixel_Stream_Base &operator<<(Color &&val) {
        if (pos_iter != m_buffer.end()) {
            *(pos_iter) = std::move(val);
            ++pos_iter;
        }
        return *this;
    }
};

#endif //SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H
