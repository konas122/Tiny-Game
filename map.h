#ifndef MAP_H
#define MAP_H

#include <cstdlib>


struct Map {
    size_t w, h;

    Map();

    int get(const size_t i, const size_t j) const ;

    bool is_empty(const size_t i, const size_t j) const ;

    bool is_close(const float i, const float j) const ;
};



#endif 
