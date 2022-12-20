#include "Map.hpp"
#include "TextureManager.hpp"

int lvl_1[20][25] = {
    {0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,2,2,2,0,2,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,0,0,0,0,2,2,0,0,0,0,2,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map() {
    dirt = TextureManager::loadTexture("assets/dirt.png");
    grass = TextureManager::loadTexture("assets/grass.png");
    acid = TextureManager::loadTexture("assets/acid.png");

    loadMap(lvl_1);

    src_rect.x = src_rect.y = 0;
    src_rect.w = dst_rect.w = 32;
    src_rect.h = dst_rect.h = 32;

    dst_rect.x = dst_rect.y = 0;
}

Map::~Map() {
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(acid);
    SDL_DestroyTexture(dirt);
}

void Map::loadMap(int arr[20][25]) {
    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 25; column++) {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::drawMap() {
    int type = 0;
    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 25; column++) {
            type = map[row][column];

            dst_rect.x = column * 32;
            dst_rect.y = row * 32;

            switch (type)
            {
            case 0:
                TextureManager::draw(grass, src_rect, dst_rect);
                break;
            case 1:
                TextureManager::draw(dirt, src_rect, dst_rect);
                break;
            case 2:
                TextureManager::draw(acid, src_rect, dst_rect);
                break;
            default:
                break;
            }
        }
    }
}