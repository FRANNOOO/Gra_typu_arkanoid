#include "Paletka.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Paletka::Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in) {
    x = x_in;
    y = y_in;
    szerokosc = szerokosc_in;
    wysokosc = wysokosc_in;
    shape.setSize(sf::Vector2f(szerokosc, wysokosc));
    shape.setOrigin(sf::Vector2f(szerokosc/2, wysokosc/2));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Blue);
};

void Paletka::przesun(float x_in) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        x = x - x_in;
        shape.setPosition(sf::Vector2f(x, y));
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        x = x + x_in;
        shape.setPosition(sf::Vector2f(x, y));
        }
}

void Paletka::ograniczRuch(float width) {
    if (x - szerokosc/2 <= 0) {
        x = 0 + szerokosc/2;
    }
    if (x + szerokosc/2 > width) {
        x = width - szerokosc/2;
    }
    shape.setPosition(sf::Vector2f(x, y));
};
void Paletka::draw(sf::RenderTarget &window) {
    window.draw(shape);
}

void Paletka::setPosition(float x_save) {
    x = x_save;
    shape.setPosition(sf::Vector2f(x, y));
}
