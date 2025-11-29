//
// Created by bonfr on 24.11.2025.
//

#include "GameSave.h"
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
#include "game.h"
#include "Stone.h"
#include <string>
#include <fstream>



GameSave::GameSave() {
}

void GameSave::capture (const Paletka& pal,const Pilka& pil,const std::vector<Stone>& stoneVec) {
    paddlePosition = pal.getX();
    ballPosition.x = pil.getX();
    ballPosition.y = pil.getY();
    ballVelocity.x = pil.getVx();
    ballVelocity.y = pil.getVy();

    blocks.clear();
    blocks.reserve(stoneVec.size());

    for (const auto& s : stoneVec)
    {
        if (s.isDestroyed())
        {
            continue;
        }

        BlockData b{};
        auto pos = s.getPosition();
        b.x  = pos.x;
        b.y  = pos.y;
        b.hp = s.getHP();

        blocks.push_back(b);
    }
}

void GameSave::apply(Paletka& p, Pilka& b, Game& g, std::vector<Stone>& stones) {
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);
    stones.clear();
    sf::Vector2f size(g.getX(), g.getY());
    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), size, data.hp);
    };
};

bool GameSave::saveToFile(const std::string& filename) {
    std::ofstream out(filename);

    if (!out.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku do zapisu: " << filename << "\n";
        return false;
    }


    out << "PADDLE "<< paddlePosition << "\n";

    out << "BALL "
        << ballPosition.x << " "
        << ballPosition.y << " "
        << ballVelocity.x << " "
        << ballVelocity.y << "\n";

    out << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& b : blocks)
    {
        out << b.x << " " << b.y << " " << b.hp << "\n";
    }

    return true;
};

bool GameSave::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);

    if (!in.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku do wczyania: " << filename << "\n";
        return false;
    }

    std::string line;

    if (in >> line >> paddlePosition) {
        // Dane wczytane do zmiennych tymczasowych w GameState
    }
    // 2. Wczytaj Piłkę
    if (in >> line >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) {
        // ...
    }
    // 3. Wczytaj Bloki
    int blocksCount;
    in >> line >> blocksCount;

    blocks.clear(); // Czyścimy stare dane
    for (int i = 0; i < blocksCount; ++i) {
        float x, y;
        int hp;
        in >> x >> y >> hp;
        blocks.push_back({x, y, hp});
    }
    in.close();
    return true;

};