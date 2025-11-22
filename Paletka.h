//
// Created by bonfr on 03.11.2025.
//

#ifndef SFML_PALETKA_H
#define SFML_PALETKA_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Paletka {
public:
    inline Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in);
    inline void przesun( float x_in);
    inline void ograniczRuch (float width);

    //-- metody pobierarajace dane pilki

    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline float getSzerokosc() const { return szerokosc; }
    inline float getWysokosc() const { return wysokosc; }

    inline void draw(sf::RenderTarget &window);
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    sf::RectangleShape shape;
};

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
    x = x + x_in;
    shape.setPosition(sf::Vector2f(x, y));
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

#endif //SFML_PALETKA_H


