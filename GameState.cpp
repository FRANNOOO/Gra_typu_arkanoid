//
// Created by bonfr on 05.12.2025.
//

#include "GameState.h"


GameState::GameState() : state(GamePhase::Menu) {}

GamePhase GameState::get() const { return state; }

void GameState::set(GamePhase newState) { state = newState; }

bool GameState::isMenu() const { return state == GamePhase::Menu; }

bool GameState::isPlaying() const { return state == GamePhase::Playing; }

bool GameState::isScores() const { return state == GamePhase::Scores; }

bool GameState::isExiting() const { return state == GamePhase::Exiting; }