//
// Created by bonfr on 22.11.2025.
//

#include <C:\Users\bonfr\CLionProjects\untitled\menu.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

Menu::Menu(float width, float height)
{	//laduj czcionke


    if (!font.openFromFile("arial.ttf"))
    {
        return;
    }
    sf::Text t(font);//w SFML 3 obiekt Text musi miec konstruktor z par font
    //rysowanie elementow menu
    t.setFont(font);
    t.setFillColor(sf::Color::Red);
    t.setString("Nowa gra");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
    menu.push_back(t);
    t.setFont(font);
    t.setFillColor(sf::Color::White);
    t.setString("Ostatnie wyniki");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
    menu.push_back(t);
    t.setFont(font);
    t.setFillColor(sf::Color::White);
    t.setString("Wyjscie");
    t.setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
    menu.push_back(t);
}

//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < menu.size(); i++)
    {
        window.draw(menu[i]);
    }
}


void Menu::przesunG()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = MAX_LICZBA_POZIOMOW - 1;
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }


}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= MAX_LICZBA_POZIOMOW)
            selectedItem = 0;
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }

}

//funklcja opozniajaca
void Menu::myDelay(int opoznienie)
{
    sf::Clock zegar;
    sf::Time czas;
    while (1)
    {
        czas = zegar.getElapsedTime();
        if (czas.asMilliseconds() > opoznienie)
        {
            zegar.restart();
            break;
        }

    }
}