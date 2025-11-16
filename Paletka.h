//
// Created by bonfr on 03.11.2025.
//

#ifndef SFML_PALETKA_H
#define SFML_PALETKA_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Paletka {
public:
    Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float vx_in);
    void przesunLewo();
    void przesunPrawo();
    void ograniczRuch (float width);

    //-- metody pobierarajace dane pilki

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }

    void draw(sf::RenderTarget &window);
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float vx;
    sf::RectangleShape shape;
};

Paletka::Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float vx_in) {
    x = x_in;
    y = y_in;
    szerokosc = szerokosc_in;
    wysokosc = wysokosc_in;
    vx = vx_in;
    shape.setSize(sf::Vector2f(szerokosc, wysokosc));
    shape.setOrigin(sf::Vector2f(szerokosc/2, wysokosc/2));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Blue);
};

void Paletka::przesunLewo() {
    x = x - vx;
    shape.setPosition(sf::Vector2f(x, y));
}
void Paletka::przesunPrawo() {
    x = x + vx;
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


