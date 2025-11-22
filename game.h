//
// Created by bonfr on 17.11.2025.
//

#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <C:\Users\bonfr\CLionProjects\untitled\Paletka.h>
#include <C:\Users\bonfr\CLionProjects\untitled\Pilka.h>
#include <C:\Users\bonfr\CLionProjects\untitled\Stone.h>
#include <optional>

constexpr unsigned int width  = 1400;
constexpr unsigned int height = 900;

class Game {
    public:
    Game();
    int update(sf::Time deltaTime);
    void render(sf::RenderTarget& target);
    bool wszystkieBlokiZniszczone();

private:
    sf::Clock deltaClock;
    Paletka pal;
    Pilka pilka;
    std::vector<Stone> bloki;

    float paddleSpeed = 400.f; // piksele na sekundę

};


#endif //SFML_GAME_H