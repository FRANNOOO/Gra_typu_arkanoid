//
// Created by bonfr on 05.12.2025.
//

#ifndef SFML_APPLICATION_H
#define SFML_APPLICATION_H

#include "GameState.h"
#include "GameSave.h"
#include "Scoreboard.h"
#include "game.h"
#include "menu.h"

class Application {
public:
    Application();
    int run();

private:
    void handleEvents();
    void update(sf::Time dt);
    void updatePlayingState(sf::Time dt);
    void render();
    void startNewGame();
    void loadSavedGame();

    sf::RenderWindow window;
    sf::Font font;
    Menu menu;
    Game game;
    GameSave save;
    GameState currentState;
    sf::Clock gameClock;
    sf::Clock frameClock;
    Scoreboard scoreboard;
};


#endif //SFML_APPLICATION_H