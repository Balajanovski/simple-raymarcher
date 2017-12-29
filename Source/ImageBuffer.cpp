//
// Created by Balajanovski on 2/04/2017.
//

#include "ImageBuffer.h"
#include "ByteColor.h"

#include <png.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>

ImageBuffer::ImageBuffer(std::shared_ptr<Screen<int>>& screen_dimensions, const std::string &src) :
        PixelBufferBase(screen_dimensions), file_src(src) { }

void ImageBuffer::flush() {
    fp = fopen(file_src.c_str(), "wb");
    if (!fp) {
        std::ostringstream ss;
        ss << "error: Unable to open file " << file_src << " for writing";
        throw std::runtime_error(ss.str());
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) {
        throw std::runtime_error("error: png_create_write_struct failed");
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        throw std::runtime_error("error: png_create_info_struct failed");
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        throw std::runtime_error("Error during init_io");
    }

    png_init_io(png_ptr, fp);

    // Write header (8 bit colour depth)
    png_set_IHDR(png_ptr, info_ptr, m_screen->width(), m_screen->height(),
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = "Title";
    title_text.text = (char *)file_src.c_str();
    png_set_text(png_ptr, info_ptr, &title_text, 1);

    png_write_info(png_ptr, info_ptr);

    std::vector<ByteColor> row(3 * m_screen->width());
    auto first = get_buffer().begin();
    auto last = get_buffer().begin() + m_screen->width();

    while (first != get_buffer().end()) {

        // Copy the color values from the buffer and convert
        // them to ByteColor for use by libPNG
        for (auto iter = first; iter != last; ++iter) {
            row.push_back(ByteColor{static_cast<unsigned char>(255 * iter->r()),
                                    static_cast<unsigned char>(255 * iter->g()),
                                    static_cast<unsigned char>(255 * iter->b())});
        }

        png_write_row(png_ptr, (png_bytep)&row[0]);
        row.clear();

        // Iterate along the buffer
        first = last;
        last += m_screen->width();
    }

    png_write_end(png_ptr, NULL);

    png_init_io(png_ptr, fp);
}

ImageBuffer::~ImageBuffer() {
    if (fp) {
        fclose(fp);
    }
    if (info_ptr){
        png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    }
    if (png_ptr) {
        png_destroy_write_struct(&png_ptr, static_cast<png_infopp>(NULL));
    }
}
