#pragma once
#include <string>

class Map {
    public:
        Map();
        ~Map();

        static void loadMap(std::string path, int size_x, int size_y);

    private:
};