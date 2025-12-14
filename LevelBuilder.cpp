#include "LevelBuilder.h"

float LevelBuilder::blockWidth(unsigned int windowW, const Settings& s) {
    return (windowW - (s.columns - 1) * s.gap) / s.columns;
}

std::vector<Stone> LevelBuilder::buildDefault(unsigned int windowW, const Settings& s) {
    const float blockW = blockWidth(windowW, s);

    std::vector<Stone> blocks;
    blocks.reserve(s.columns * s.rows);

    for (int y = 0; y < s.rows; ++y) {
        for (int x = 0; x < s.columns; ++x) {
            float posX = x * (blockW + s.gap);
            float posY = s.topOffset + y * (s.blockH + s.gap);

            int L = (y < 1) ? 3
                  : (y < 3) ? 2
                             : 1;

            blocks.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(blockW, s.blockH),
                L
            );
        }
    }
    return blocks;
}