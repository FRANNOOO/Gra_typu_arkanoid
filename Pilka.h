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
    void przesun(float dt);
    void odbijX();
    void odbijY();
    void kolizjaSciana(float w, float h);
    bool kolizjaPaletka(const Paletka &p);
    void reset(sf::Vector2f position, sf::Vector2f velocity);
    void draw(sf::RenderTarget &window);

    //-- metody pobierarajace dane pilki
    float getX() const { return x; };
    float getY() const { return y; };
    float getVx() const { return vx; };
    float getVy() const { return vy; };
    float getRadius() const { return radius; };

private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    sf::CircleShape shape;
};

#endif //SFML_PILKA_H