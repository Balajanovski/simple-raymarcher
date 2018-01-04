// 
// Created by Balajanovski on 15/12/2017.
//

#ifndef SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H
#define SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H

#include <vector>
#include <algorithm>
#include <memory>

#include "Color.h"
#include "Screen.h"

class PixelBufferBase {
private:
    // Stores the pixel data
    std::vector<Color> m_buffer;
protected:
    std::vector<Color> &get_buffer() {
        return m_buffer;
    }

    // Represents the size of the screen
    std::shared_ptr<Screen<int>> m_screen;
public:
    PixelBufferBase(std::shared_ptr<Screen<int>>& bnd) :
            m_buffer(bnd->size()), m_screen(bnd) { }
    virtual ~PixelBufferBase() { };
    virtual void flush() = 0;
    virtual void clear() { std::fill(get_buffer().begin(), get_buffer().end(), Color{0, 0, 0}); }

    void add_to_buffer(int x, int y, Color&& val) {

        m_buffer[y * m_screen->width() + x] = val;

    }
};

#endif //SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H
