#pragma once
#include <string>

class Map {
    public:
        Map(std::string id);
        ~Map();

        void addTile(int src_x, int src_y, int x_pos, int y_pos);
        void loadMap(std::string path, int size_x, int size_y);

    private:
        std::string texture_id;
};