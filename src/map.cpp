#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS/Components.hpp"

extern Manager manager;

Map::Map(const char* m_file_path) 
: file_path(m_file_path) {}

Map::~Map() {
}

void Map::loadMap(std::string path, int size_x, int size_y) {
    char c;
    std::fstream map_file;
    map_file.open(path);

    int src_x, src_y;

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            map_file.get(c);
            src_y = atoi(&c) * 32;
            map_file.get(c);
            src_x = atoi(&c) * 32;
            addTile(src_x, src_y, x*32, y*32);
            map_file.ignore();
        }
    }

    map_file.ignore();

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            map_file.get(c);
            if(c == '1') { 
                Entity& terrain_collider(manager.addEntity());
                terrain_collider.addComponent<ColliderComponent>("terrain", x*32, y*32);
                terrain_collider.addGroup(Game::group_collider);
            }
            map_file.ignore();
        }
    }

    map_file.close();
}

void Map::addTile(int src_x, int src_y, int x_pos, int y_pos) {
    Entity& tile(manager.addEntity());
    tile.addComponent<TileComponent>(src_x, src_y, x_pos, y_pos, file_path);
    tile.addGroup(Game::group_map);
}