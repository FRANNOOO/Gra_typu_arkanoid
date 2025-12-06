#include "Scoreboard.h" // tablica wyników gry

#include <cmath>
#include <iomanip>
#include <sstream>

Scoreboard::Scoreboard() : font(nullptr), hintTimer(0.f) {} // start bez czcionki i z timerem

void Scoreboard::setFont(const sf::Font& fontRef) {
    font = &fontRef; // przypisanie czcionki
    dynamicHint.emplace(fontRef, "ESC - wyjscie", 28); // tekst z podpowiedzią na dole ekranu
    dynamicHint->setFillColor(sf::Color(255, 255, 255, 180));
    dynamicHint->setPosition(sf::Vector2f(width / 3.f, height - 120.f));
}

void Scoreboard::addResult(bool wygrana, sf::Time czasGry) {
    historiaWynikow.push_back({wygrana, czasGry}); // zapis wyniku
    if (historiaWynikow.size() > 5) {
        historiaWynikow.erase(historiaWynikow.begin()); // limit historii
    }
}

void Scoreboard::render(sf::RenderTarget& target) {
    if (!font) {
        return; // jeśli brak czcionki, nie ma co rysować
    }

    sf::Text tytul(*font, "Ostatnie wyniki", 48); // nagłówek
    tytul.setFillColor(sf::Color::Cyan);
    tytul.setPosition(sf::Vector2f(width / 3.f, 80.f));
    target.draw(tytul);

    float startY = 180.f;
    unsigned int indeks = 1;

    if (historiaWynikow.empty()) { // brak wyników
        sf::Text brak(*font, "Brak wynikow. Rozegraj pierwsza gre!", 28);
        brak.setFillColor(sf::Color::White);
        brak.setPosition(sf::Vector2f(width / 3.5f, startY));
        target.draw(brak);
    } else {
        for (auto it = historiaWynikow.rbegin(); it != historiaWynikow.rend(); ++it) { // od najnowszego
            std::ostringstream opisWyniku;
            opisWyniku << indeks << ". " << (it->wygrana ? "Wygrana" : "Przegrana")
                       << " - " << std::fixed << std::setprecision(1)
                       << it->czasGry.asSeconds() << " s"; // format czasu

            sf::Text wynik(*font, opisWyniku.str(), 32);
            wynik.setFillColor(sf::Color::White);
            wynik.setPosition(sf::Vector2f(width / 4.f, startY));
            target.draw(wynik);

            startY += 50.f; // odstępy między linijkami
            ++indeks;
        }
    }

    if (dynamicHint) {
        target.draw(*dynamicHint); // pulsująca podpowiedź
    }
}

void Scoreboard::updateHint(sf::Time dt) {
    if (!dynamicHint) return;

    hintTimer += dt.asSeconds(); // czas do animacji
    float puls = 0.5f + 0.5f * std::sin(hintTimer * 2.5f); // efekt migania

    sf::Color baseColor = dynamicHint->getFillColor();
    baseColor.a = static_cast<decltype(baseColor.a)>(120 + puls * 120);
    dynamicHint->setFillColor(baseColor);

    float scale = 1.f + 0.05f * std::sin(hintTimer * 3.5f); // delikatny zoom
    dynamicHint->setScale({scale, scale});
}

void Scoreboard::resetHint() {
    hintTimer = 0.f; // reset animacji
    if (dynamicHint) {
        dynamicHint->setScale({1.f, 1.f}); // powrót do rozmiaru
    }
}