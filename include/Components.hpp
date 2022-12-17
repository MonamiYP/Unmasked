#pragma once
#include "ECS.hpp"

class PositionComponent : public Component {
    public:
        int x() { return x_pos; }
        int y() { return y_pos; }

        void init() override {
            x_pos = 0;
            y_pos = 0;
        }
        void update() override {
            x_pos++;
            y_pos++;
        }
        void setPos(int x, int y) {
            x_pos = x;
            y_pos = y;
        }

    private:
        int x_pos, y_pos;
};