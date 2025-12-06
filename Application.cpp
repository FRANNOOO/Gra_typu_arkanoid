#include "Application.h"
#include "GameState.h"

#include <iostream>

Application::Application()
    : window(sf::VideoMode({width, height}), "My window"), // Tworzenie okna o zadanym rozmiarze
      menu(window.getSize().x, window.getSize().y), // Inicjalizacja menu z rozmiarem okna
      menuLocked(false) { // Flaga blokady menu
    if (!font.openFromFile("arial.ttf")) { // Proba wczytania czcionki
        std::cerr << "Nie mozna zaladowac czcionki arial.ttf" << std::endl; // Komunikat bledu
    }

    scoreboard.setFont(font); // Ustawienie czcionki dla tablicy wyników
}

int Application::run() {
    while (window.isOpen()) { // Petla glowna programu — dziala dopki okno otwarte
        sf::Time dt = frameClock.restart(); // Mierzenie czasu miedzy klatkami
        handleEvents(); // Obsluga zdarzen uzytkownika
        update(dt); // Aktualizacja stanu gry na podstawie uplywu czasu
        render(); // Rysowanie sceny na ekranie

    }
    std::cout << "Gra uruchomiona" << std::endl; // Informacja po zakonczeniu dzialania petli
    return 0;
}

void Application::handleEvents() {
    while (const std::optional event = window.pollEvent()) { // Pobieranie zdarzen z okna
        if (event->is<sf::Event::Closed>()) { // Jesli kliknieto zamkniecie okna
            window.close(); // Zamkniecie aplikacji
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) { // Obsluga wcisniecia klawiszy
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up) { // Strzalka w gore
                menu.myDelay(250); // Opoznienie ruchu w menu
                menu.przesunG(); // Przesuniecie opcji w gore
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::Down) { // Strzalka w dol
                menu.myDelay(250); // Opoznienie ruchu w menu
                menu.przesunD(); // Przesuniecie opcji w dol
            }

            if (!menuLocked) { // Dzialania dostepne tylko gdy menu nie zablokowane
                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 0) { // Opcja "Nowa Gra"
                    startNewGame();
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 1) { // Opcja "Wczytaj gre"
                    loadSavedGame();
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 2) { // Opcja "Wyniki"
                    currentState.set(GamePhase::Scores); // Zmiana stanu aplikacji
                    scoreboard.resetHint(); // Reset podpowiedzi wyniku
                    menuLocked = true; // Zablokowanie menu
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 3) { // Opcja "Wyjscie"
                    currentState.set(GamePhase::Exiting); // Przejscie do fazy zamykania
                    menuLocked = true; // Blokada menu
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::T && currentState.isMenu()) { // Klawisz T wlacza ruch ozdób menu
                    menu.ustawRuchOzdoby(true);
                }
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) { // ESC — powrot do menu
        resetToMenu();
    }
}

void Application::update(sf::Time dt) {
    if (currentState.isExiting()) { // Gdy ustawiono zamykanie gry
        window.close();
        return;
    }

    if (currentState.isPlaying()) { // Aktualizacja gry podczas rozgrywki
        updatePlayingState(dt);
    } else if (currentState.isMenu()) { // Aktualizacja menu gry
        menu.update(dt.asSeconds(), window.getSize());
    } else if (currentState.isScores()) { // Aktualizacja ekranu wyników
        scoreboard.updateHint(dt);
    }
}

void Application::updatePlayingState(sf::Time dt) {
    int wynik = game.update(dt); // Aktualizacja logiki gry i pobranie wyniku
    if (wynik != 0) { // Sprawdzenie czy gra sie zakonczyla
        bool wygrana = wynik == 2; // Czy gracz wygral?
        sf::Time czasGry = gameClock.getElapsedTime(); // Czas trwania rozgrywki
        scoreboard.addResult(wygrana, czasGry); // Zapis rezultatu do tabeli
        resetToMenu(); // Powrot do menu
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) { // Klawisz P zapisuje gre
        save.capture(game.getPaletka(), game.getPilka(), game.getBloki()); // Pobranie stanu gry
        save.saveToFile("savegame.txt"); // Zapis do pliku
        std::cout << "Gra zapisana!"; // Informacja dla gracza
    }
}

void Application::render() {
    window.clear(); // Czyszczenie bufora rysowania

    if (currentState.isPlaying()) { // Widok gry
        game.render(window);
    } else if (currentState.isMenu()) { // Widok menu
        menu.draw(window);
    } else if (currentState.isScores()) { // Widok wyników
        renderScores();
    } else if (currentState.isExiting()) { // Przy wychodzeniu
        window.close();
    }

    window.display(); // Wyswietlenie zawartosci
}

void Application::renderScores() {
    scoreboard.render(window); // Render tabeli wyników
}

void Application::resetToMenu() {
    currentState.set(GamePhase::Menu); // Powrot do menu glownego
    menuLocked = false; // Odbokowanie menu
    scoreboard.resetHint(); // Reset tipow
}

void Application::startNewGame() {
    game = Game(); // Nowa instancja gry
    currentState.set(GamePhase::Playing); // Przejscie do gry
    menuLocked = true; // Zablokowanie menu
    gameClock.restart(); // Restart czasu gry
}

void Application::loadSavedGame() {
    if (save.loadFromFile("savegame.txt")) { // Wczytanie zapisu gry
        save.apply(game.getPaletka(), game.getPilka(), game, game.getBloki()); // Przywrocenie stanu gry
        currentState.set(GamePhase::Playing); // Powrot do gry
        menuLocked = true; // Zablokowanie menu
        gameClock.restart(); // Restart zegara
    }
}
