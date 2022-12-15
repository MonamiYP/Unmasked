#pragma once
#include "Game.hpp"

class Map {
    public:
        Map();
        ~Map();

        void loadMap(int arr[20][25]);
        void drawMap();

    private:
        SDL_Rect src_rect, dst_rect;

        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* acid;

        int map[20][25];
};