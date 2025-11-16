//
// Created by bonfr on 03.11.2025.
//

#ifndef SFML_PILKA_H
#define SFML_PILKA_H


#include <iostream>
#include "Paletka.h"
#include <SFML/Graphics.hpp>

class Pilka {
public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in);
    void przesun();
    void odbijX();
    void odbijY();
    void kolizjaSciana(float w, float h);
    bool kolizjaPaletka(const Paletka &p);

    //-- metody pobierarajace dane pilki

    float getX() { return x; };
    float getY() { return y; };
    float getVx() { return vx; };
    float getVy() { return vy; };
    float getRadius() { return radius; };

    void draw(sf::RenderTarget &window);

private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    sf::CircleShape shape;

};
Pilka::Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in) {
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;
    radius = radius_in;
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius)); // żeby (x,y) było środkiem
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::White);

};



void Pilka::przesun() {
    x = x + vx;
    y = y + vy;
    shape.setPosition(sf::Vector2f(x, y));

}
void Pilka::odbijX() {
    vx = -vx;
};
void Pilka::odbijY() {
    vy = -vy;
};
void Pilka::kolizjaSciana(float width, float height) {
    if (x - radius <= 0 || x + radius >= width) {
        odbijX();
    }
    if (y - radius <= 0) {
        odbijY();
    }
};

bool Pilka::kolizjaPaletka(const Paletka &p) {
    float left   = p.getX() - p.getSzerokosc() / 2.f;
    float right  = p.getX() + p.getSzerokosc() / 2.f;
    float top    = p.getY() - p.getWysokosc() / 2.f;
    float bottom = p.getY() + p.getWysokosc() / 2.f;

    bool overlapX = (x + radius >= left) && (x - radius <= right);
    bool overlapY = (y + radius >= top) && (y - radius <= bottom);

    if (overlapX && overlapY && vy > 0.f) {  // piłka leci w dół na paletkę
        vy = -std::abs(vy);
        y = top - radius; // ustaw nad paletką
        shape.setPosition(sf::Vector2f(x, y));
        return true;
    }
    return false;
}

void Pilka::draw(sf::RenderTarget &window) {
    window.draw(shape);
}
#endif //SFML_PILKA_H