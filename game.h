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

class Game {
    public:
    Game();
    void run();
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    bool wszystkieBlokiZniszczone();

private:
    sf::Clock deltaClock;
    Paletka pal;
    Pilka pilka;
    std::vector<Stone> bloki;

    float width  = 900;
    float height = 600;
    sf::RenderWindow window;

};


#endif //SFML_GAME_H