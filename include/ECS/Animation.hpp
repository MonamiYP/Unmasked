#pragma once

class Animation {
    public:
        int index;
        int frames;
        int speed;

        Animation() {}
        Animation(int m_index, int m_frames, int m_speed) {
            index = m_index;
            frames = m_frames;
            speed = m_speed;
        }
};