#pragma once
#include <string>

class Map {
    public:
        Map(const char* m_file_path);
        ~Map();

        void addTile(int src_x, int src_y, int x_pos, int y_pos);
        void loadMap(std::string path, int size_x, int size_y);

    private:
        const char* file_path;
};