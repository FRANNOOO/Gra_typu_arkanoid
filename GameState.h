//
// Created by bonfr on 05.12.2025.
//

#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

enum class GamePhase { Menu, Playing, Scores, Exiting };

class GameState {
public:
    GameState();

    GamePhase get() const;
    void set(GamePhase newState);

    bool isMenu() const;
    bool isPlaying() const;
    bool isScores() const;
    bool isExiting() const;

private:
    GamePhase state;
};


#endif //SFML_GAMESTATE_H