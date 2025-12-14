//
// Created by bonfr on 05.12.2025.
//

#ifndef SFML_SCOREBOARD_H
#define SFML_SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

#include "game.h"

struct WynikGry {
    bool wygrana;
    sf::Time czasGry;
};

class Scoreboard {
public:
    Scoreboard();

    void setFont(const sf::Font& font);

    void addResult(bool wygrana, sf::Time czasGry);
    void render(sf::RenderTarget& target);
    void updateHint(sf::Time dt);

private:
    const sf::Font* font;
    std::vector<WynikGry> historiaWynikow;
    std::optional<sf::Text> dynamicHint;
    float hintTimer;

};

#endif //SFML_SCOREBOARD_H