#ifndef TINYDOOM_H
#define TINYDOOM_H

#include <vector>

#include "map.h"
#include "player.h"
#include "sprite.h"
#include "framebuffer.h"
#include "textures.h"


struct GameState {
    Map map;
    Players player;
    std::vector<Sprite> monsters;
    Texture tex_walls;
    Texture tex_monst;
};

void render(FrameBuffer &fb, GameState &gs);

#endif
