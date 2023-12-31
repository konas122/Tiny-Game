#ifndef TEXTURES_H
#define TEXTURES_H

#include <vector>
#include <string>
#include <cstdint>


struct Texture {
    size_t img_w, img_h;
    size_t count, size;
    std::vector<uint32_t> img;

    Texture(const std::string filename, const uint32_t format);

    uint32_t &get(const size_t i, const size_t j, const size_t idx);

    std::vector<uint32_t> get_scaled_column(const size_t texure_id, const size_t tex_coord, const size_t column_height);
};

#endif
