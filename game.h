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
    Paletka& getPaletka()             { return pal; }
    const Paletka& getPaletka() const { return pal; }

    Pilka& getPilka()             { return pilka; }
    const Pilka& getPilka() const { return pilka; }

    std::vector<Stone>& getBloki()             { return bloki; }
    const std::vector<Stone>& getBloki() const { return bloki; }


    float getX() const { return ROZMIAR_BLOKU_X; };
    float getY() const { return ROZMIAR_BLOKU_Y; };

private:
    sf::Clock deltaClock;
    Paletka pal;
    Pilka pilka;
    std::vector<Stone> bloki;

    float ROZMIAR_BLOKU_Y;
    float ROZMIAR_BLOKU_X;

    float paddleSpeed = 400.f; // piksele na sekundę

};


#endif //SFML_GAME_H