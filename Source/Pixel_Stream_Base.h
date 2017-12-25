// 
// Created by Balajanovski on 15/12/2017.
//

#ifndef SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H
#define SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H

#include <vector>
#include <mutex>

#include "Color.h"
#include "Screen.h"

class Pixel_Stream_Base {
private:
    // Stores the pixel data
    std::vector<Color> m_buffer;

    std::mutex m_mutex;
protected:
    std::vector<Color> &get_buffer() {
        return m_buffer;
    }

    // Represents the size of the screen
    Screen<int>* m_screen;
public:
    Pixel_Stream_Base(Screen<int>* bnd) :
            m_buffer(bnd->size()), m_screen(bnd) { }
    virtual ~Pixel_Stream_Base() { };
    virtual void flush() = 0;
    virtual void clear() = 0;

    void add_to_buffer(int x, int y, Color&& val) {

        m_buffer[y * m_screen->width() + x] = val;

    }
};

#endif //SIMPLE_RAYTRACER_PIXEL_STREAM_BASE_H
