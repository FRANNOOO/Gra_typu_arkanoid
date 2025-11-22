#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <C:\Users\bonfr\CLionProjects\untitled\Game.h>
#include <C:\Users\bonfr\CLionProjects\untitled\menu.h>

enum class GameState { Menu, Playing, Scores, Exiting };

struct WynikGry {
    bool wygrana;
    sf::Time czasGry;
};


int main()
{

    int menu_selected_flag = 0;
    sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "My window"
    );
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Nie mozna zaladowac czcionki arial.ttf" << std::endl;
        return 1;
    }
    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    sf::Clock gameClock;
    std::vector<WynikGry> historiaWynikow;
    sf::Clock clock; // zegar do dt

    //Zegar do dynamicznego tekstu
    sf::Text dynamicHint(font);
    float hintTimer = 0.f;

    // petla wieczna - dopoki okno jest otwarte
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();  // czas od poprzedniej klatki

        // w kazdej iteracji petli sprawdzaj zdarzenia

        while (const std::optional event = window.pollEvent())
        {
            // jezeli odebrano zdarzenie "Closed" zamknij okno
            if (event->is<sf::Event::Closed>())
                window.close();
            //jezeli nacisnieto jakikolwiek przycisk
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {//obsluga menu z poziomu klawiszy (strzalki)
                if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    menu.myDelay(250);
                    menu.przesunG();
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                {
                    menu.myDelay(250);
                    menu.przesunD();
                }
                if (menu_selected_flag == 0)
                {//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 0)
                    {
                        game = Game();
                        currentState = GameState::Playing; // Zmiana stanu
                        menu_selected_flag = 1;
                    }

                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 1)
                    {
                        currentState = GameState::Scores;
                        menu_selected_flag = 1;
                    }

                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 2)
                    {
                        currentState = GameState::Exiting;
                        menu_selected_flag = 1;
                    }

                    // start ruchu ozdoby po T
                    if (keyPressed->scancode == sf::Keyboard::Scancode::T &&
                        currentState == GameState::Menu)
                    {
                        menu.ustawRuchOzdoby(true);   // albo przelaczRuchOzdoby();
                    }

                }


            }
        }

        if (currentState == GameState::Playing)
        {
            // jeśli nie korzystasz z dt w Game::update, możesz dać sf::Time::Zero
            int wynik = game.update(dt);
            if (wynik != 0) {
                currentState = GameState::Menu;
                menu_selected_flag = 0;
                bool wygrana = false;
                if (wynik == 2) {
                    bool wygrana = 1;
                }
                sf::Time czasGry = gameClock.getElapsedTime();
                historiaWynikow.push_back({wygrana, czasGry});
                if (historiaWynikow.size() > 5) {
                    historiaWynikow.erase(historiaWynikow.begin());
                }
            }
        }

        // wyczysc obszar rysowania
        window.clear();

        // window.draw(...);
        if (currentState == GameState::Menu)
        {
            menu.update(dt.asSeconds(), window.getSize());
            menu.draw(window);
        }


        else if (currentState == GameState::Playing)

            game.render(window);

        else if (currentState == GameState::Exiting)

            window.close();

         else if (currentState == GameState::Scores)
        {
            sf::Text tytul(font, "Ostatnie wyniki", 48);
            tytul.setFillColor(sf::Color::Cyan);
            tytul.setPosition(sf::Vector2f(width / 3.f, 80.f));
            window.draw(tytul);

            float startY = 180.f;
            unsigned int indeks = 1;
            if (historiaWynikow.empty()) {
                sf::Text brak(font,"Brak wynikow. Rozegraj pierwsza gre!", 28);
                brak.setFillColor(sf::Color::White);
                brak.setPosition(sf::Vector2f(width / 3.5f, startY));
                window.draw(brak);
            } else {
                for (auto it = historiaWynikow.rbegin(); it != historiaWynikow.rend(); ++it) {
                    std::ostringstream opisWyniku;
                    opisWyniku << indeks << ". " << (it->wygrana ? "Wygrana" : "Przegrana")
                               << " - " << std::fixed << std::setprecision(1)
                               << it->czasGry.asSeconds() << " s";

                    sf::Text wynik(font, opisWyniku.str(), 32);
                    wynik.setFillColor(sf::Color::White);
                    wynik.setPosition(sf::Vector2f(width / 4.f, startY));
                    window.draw(wynik);

                    startY += 50.f;
                    ++indeks;
                }
            }

             dynamicHint.setFont(font);
             dynamicHint.setCharacterSize(28);
             dynamicHint.setFillColor(sf::Color(255, 255, 255, 180));
             dynamicHint.setString("ESC - wyjscie");
             dynamicHint.setPosition(sf::Vector2f(width / 3.f, height - 120.f));


             hintTimer += dt.asSeconds();

             float puls = 0.5f + 0.5f * std::sin(hintTimer * 2.5f);
             sf::Color baseColor = dynamicHint.getFillColor();
             baseColor.a = static_cast<decltype(baseColor.a)>(120 + puls * 120);
             dynamicHint.setFillColor(baseColor);

             float scale = 1.f + 0.05f * std::sin(hintTimer * 3.5f);
             dynamicHint.setScale({scale, scale});
             window.draw(dynamicHint);
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
                 currentState = GameState::Menu;
                 menu_selected_flag = 0;
             }
        }


        // ostatnia czynnosc - wyswietl okno wraz zawartoscia
        window.display();
    }

    return 0;
}