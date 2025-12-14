#ifndef SFML_PALETKA_H
#define SFML_PALETKA_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Paletka {
public:
    Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in);
    void przesun( float x_in);
    void ograniczRuch (float width);
    void draw(sf::RenderTarget &window);
    void setPosition(float x_save);

    //-- metody pobierarajace dane pilki

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }

private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    sf::RectangleShape shape;
};

#endif //SFML_PALETKA_H


