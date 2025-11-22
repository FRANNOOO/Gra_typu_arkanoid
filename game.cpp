//
// Created by bonfr on 17.11.2025.
//

#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <C:\Users\bonfr\CLionProjects\untitled\Paletka.h>
#include <C:\Users\bonfr\CLionProjects\untitled\Pilka.h>
#include <C:\Users\bonfr\CLionProjects\untitled\Stone.h>
#include <optional>

Game::Game ()
    : window(
        sf::VideoMode({width, height}),  // SFML 3: Vector2u
        "Arkanoid test",
        sf::State::Windowed              // wymagany trzeci argument
    ),
    pal(520.f, 440.f, 100.f, 20.f, 8.f), // x,y,szer,wys, predkosc
    pilka(320.f, 300.f, 4.f, 3.f, 8.f) // x,y,vx,vy,radius

    {
    window.setFramerateLimit(60);
    const int   ILOSC_KOLUMN      = 6;
    const int   ILOSC_WIERSZY     = 7;
    const float ODSTEP            = 2.f;
    const float ROZMIAR_BLOKU_Y   = 25.f;
    const float ROZMIAR_BLOKU_X   =
        (width - (ILOSC_KOLUMN - 1) * ODSTEP) / ILOSC_KOLUMN;

    bloki.reserve(ILOSC_KOLUMN * ILOSC_WIERSZY);

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {          // najpierw wiersze (Y)
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {       // potem kolumny (X)
            float posX = x * (ROZMIAR_BLOKU_X + ODSTEP);
            float posY = 50.f + y * (ROZMIAR_BLOKU_Y + ODSTEP);

            int L = (y < 1) ? 3       // pierwszy rząd: 3 HP
                  : (y < 3) ? 2       // rzędy 1–2: 2 HP
                             : 1;     // reszta: 1 HP

            bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }


}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        sf::Time dt = deltaClock.restart();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    //obsługa zdarzeń
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::update(sf::Time deltaTime) {
    //sterowanie paletką
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        pal.przesunLewo();
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        pal.przesunPrawo();
        }
    pal.ograniczRuch(width);

    //logika piłki
    pilka.przesun();
    pilka.kolizjaSciana(width, height);
    if (pilka.kolizjaPaletka(pal)) {
        std::cout << "HIT PADDLE\n";
    }

    {
        float cx = pilka.getX(); // środek piłki - X
        float cy = pilka.getY(); // środek piłki - Y

        for (Stone& blok : bloki) {
            if (blok.isDestroyed())
                continue; // ten blok już "zniknął"

            sf::FloatRect bounds = blok.getGlobalBounds();
            float left   = bounds.position.x;
            float right  = bounds.position.x + bounds.size.x;
            float top    = bounds.position.y;
            float bottom = bounds.position.y + bounds.size.y;


            // Sprawdzam, czy środek piłki jest wewnątrz prostokąta bloku
            if (cx >= left && cx <= right &&
                cy >= top  && cy <= bottom)
            {
                blok.trafienie(); // zmniejszam HP bloku

                // Proste odbicie: zawsze w pionie
                pilka.odbijY();

                // Na tej klatce piłka trafia tylko jeden blok
                break;
            }
        }
    }

    //sprawdzenie przegranej
    if (pilka.getY() - pilka.getRadius() > height) {
        std::cout << "KONIEC GRY\n";
        window.close();
    }

    if (wszystkieBlokiZniszczone()) {
        std::cout << "WYGRANA! Wszystkie bloki zniszczone.\n";
        window.close();
    }
}

void Game::render() {
    //rysowanie
    window.clear(sf::Color(20, 20, 30));
    pal.draw(window);
    pilka.draw(window);
    for (const auto& blok : bloki) {
        blok.draw(window);
    }
    window.display();
}

 bool Game::wszystkieBlokiZniszczone()
{
        for (const Stone& blok : bloki) {
            if (!blok.isDestroyed()) {
                return false; // znaleźliśmy choć jeden żywy blok
            }
        }
        return true; // żaden blok nie był żywy → wszystkie zniszczone
}