#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
#include <SDL2/SDL.h>

#include "utils.h"
#include "textures.h"


// Texture::Texture(const std::string filename) : img_w(0), img_h(0), count(0), size(0), img() {
//     int nchannels = -1, w, h;
//     unsigned char *pixmap = stbi_load(filename.c_str(), &w, &h, &nchannels, 0);
//     if (!pixmap) {
//         std::cerr << "Error: can't load the texture" << std::endl;
//         return;
//     }
//     if (nchannels != 4) {
//         std::cerr << "Error: the texture must be a 32 bit image" << std::endl;
//         stbi_image_free(pixmap);
//         return;
//     }

//     count = w / h;
//     size = w / count;
//     img_w = w;
//     img_h = h;

//     if (w != h * int(count)) {
//         std::cerr << "Error: the texture file must contain N square textures packed horizontally" << std::endl;
//         stbi_image_free(pixmap);
//         return;
//     }

//     img = std::vector<uint32_t>(w * h);
//     for (int j = 0; j < h; j++)
//         for (int i = 0; i < w; i++) {
//             int c = (i + j * w) * 4;
//             uint8_t r = pixmap[c + 0];
//             uint8_t g = pixmap[c + 1];
//             uint8_t b = pixmap[c + 2];
//             uint8_t a = pixmap[c + 3];
//             img[i + j * w] = pack_color(r, g, b, a);
//         }
//     stbi_image_free(pixmap);
// }
Texture::Texture(const std::string filename, const uint32_t format) : img_w(0), img_h(0), count(0), size(0), img() {
    SDL_Surface *tmp = SDL_LoadBMP(filename.c_str());
    if (!tmp) {
        std::cerr << "Error in SDL_LoadBMP: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(tmp, format, 0);
    SDL_FreeSurface(tmp);
    if (!surface) {
        std::cerr << "Error in SDL_ConvertSurfaceFormat: " << SDL_GetError() << std::endl;
        return;
    }

    int w = surface->w;
    int h = surface->h;

    if (w * 4 != surface->pitch) {
        std::cerr << "Error: the texture must be a 32 bit image" << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    if (w != h * int(w / h)) {
        std::cerr << "Error: the texture file must contain N square textures packed horizontally" << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    count = w / h;
    size = w / count;
    img_w = w;
    img_h = h;
    uint8_t *pixmap = reinterpret_cast<uint8_t *>(surface->pixels);

    img = std::vector<uint32_t>(w * h);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            uint8_t r = pixmap[(i + j * w) * 4 + 0];
            uint8_t g = pixmap[(i + j * w) * 4 + 1];
            uint8_t b = pixmap[(i + j * w) * 4 + 2];
            uint8_t a = pixmap[(i + j * w) * 4 + 3];
            img[i + j * w] = pack_color(r, g, b, a);
        }
    }
    SDL_FreeSurface(surface);
}


uint32_t &Texture::get(const size_t i, const size_t j, const size_t idx) {
    assert(i < size && j < size && idx < count);
    return img[i + j * img_w + idx * size];
}


std::vector<uint32_t> Texture::get_scaled_column(const size_t texture_id, const size_t tex_coord, const size_t column_height) {
    assert(tex_coord < size && texture_id < count);
    std::vector<uint32_t> column(column_height);
    for (size_t i = 0; i < column_height; i++) {
        column[i] = get(tex_coord, (i * size) / column_height, texture_id);
    }
    return column;
}
