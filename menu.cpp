//
// Created by bonfr on 22.11.2025.
//

#include <C:\Users\bonfr\CLionProjects\untitled\menu.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

Menu::Menu(float width, float height)
: font{},        // font się tworzy
backgroundSprite()
{	//laduj czcionke

    if (!backgroundTexture.loadFromFile("tlo.jpg")) {
        std::cerr << "Nie mozna wczytac tlo.jpg\n";
    }
    backgroundSprite = new sf::Sprite(backgroundTexture);

    // Obraz ma być rozciągnięty do okna:
    sf::Vector2u texSize = backgroundTexture.getSize();
    backgroundSprite->setScale(sf::Vector2f(
    width  / static_cast<float>(texSize.x),
    height / static_cast<float>(texSize.y)
));

    if (!font.openFromFile("arial.ttf"))
    {
        return;
    }

    ozdobaMenu.setRadius(32.f);
    ozdobaMenu.setOrigin(sf::Vector2f(ozdobaMenu.getRadius(), ozdobaMenu.getRadius()));
    ozdobaMenu.setPosition(sf::Vector2f(width * 0.8f, height * 0.32f));
    ozdobaMenu.setFillColor(sf::Color(255, 215, 0, 190));
    ozdobaMenu.setOutlineThickness(3.f);
    ozdobaMenu.setOutlineColor(sf::Color(100, 80, 10, 180));
    ozdobaPredkosc = sf::Vector2f(90.f, 70.f);

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

void Menu::update(float dt, sf::Vector2u windowSize)
{
    if (!ozdobaRuchAktywny)
        return;

    sf::Vector2f pos = ozdobaMenu.getPosition();
    pos += ozdobaPredkosc * dt;

    float radius = ozdobaMenu.getRadius();
    float maxX = static_cast<float>(windowSize.x);
    float maxY = static_cast<float>(windowSize.y);

    if (pos.x - radius < 0.f)
    {
        pos.x = radius;
        ozdobaPredkosc.x = std::abs(ozdobaPredkosc.x);
    }
    if (pos.x + radius > maxX)
    {
        pos.x = maxX - radius;
        ozdobaPredkosc.x = -std::abs(ozdobaPredkosc.x);
    }
    if (pos.y - radius < 0.f)
    {
        pos.y = radius;
        ozdobaPredkosc.y = std::abs(ozdobaPredkosc.y);
    }
    if (pos.y + radius > maxY)
    {
        pos.y = maxY - radius;
        ozdobaPredkosc.y = -std::abs(ozdobaPredkosc.y);
    }
    ozdobaMenu.setPosition(pos);
}

//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow &window)
{
    window.draw(*backgroundSprite);
    window.draw(ozdobaMenu);
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

void Menu::ustawRuchOzdoby(bool aktywny)
{
    ozdobaRuchAktywny = aktywny;
}
