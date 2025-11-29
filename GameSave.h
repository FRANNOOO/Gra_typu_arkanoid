//
// Created by bonfr on 24.11.2025.
//

#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "game.h"
#include <string>
#include <fstream>


class GameSave {
private:
    struct BlockData {
        float x, y;
        int hp;
    };
    float paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameSave ();
    void capture (const Paletka& pal,const Pilka& pil,const std::vector<Stone>& stoneVec);
    void apply(Paletka& p, Pilka& b, Game& g, std::vector<Stone>& stones);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
};




#endif //SFML_GAMESTATE_H