//
// Created by bonfr on 22.11.2025.
//

#ifndef SFML_MENU_H
#define SFML_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <C:\Users\bonfr\CLionProjects\untitled\Paletka.h>
#include <C:\Users\bonfr\CLionProjects\untitled\Pilka.h>
#include <C:\Users\bonfr\CLionProjects\untitled\Stone.h>
#include <optional>

class Menu {
private:
    sf::Font font;
    std::vector <sf::Text>menu;//tablica elementow Text
    int selectedItem = 0;
    int MAX_LICZBA_POZIOMOW = 3;


public:
    Menu(float width, float height);
    void przesunG();//przesun do gory
    void przesunD();//przesun w dol
    void myDelay(int opoznienie);
    int getSelectedItem() { return selectedItem; }//zwroc poziom menu
    void draw(sf::RenderWindow &window);//rysuj menu w oknie
};


#endif //SFML_MENU_H