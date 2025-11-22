#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <C:\Users\bonfr\CLionProjects\untitled\Game.h>
#include <C:\Users\bonfr\CLionProjects\untitled\menu.h>

enum class GameState { Menu, Playing, Scores, Exiting };


int main()
{

    int menu_selected_flag = 0;
    sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "My window"
    );
    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    sf::Clock clock; // zegar do dt
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
                        std::cout << "Najlepsze wyniki..." << std::endl;
                        menu_selected_flag = 1;
                    }

                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && menu.getSelectedItem() == 2)
                    {
                        currentState = GameState::Exiting;
                        menu_selected_flag = 1;
                    }

                }


            }
        }

        if (currentState == GameState::Playing)
        {
            // jeśli nie korzystasz z dt w Game::update, możesz dać sf::Time::Zero
            if (game.update(dt)) {
                currentState = GameState::Menu;
                menu_selected_flag = 0;
            }
        }

        // wyczysc obszar rysowania
        window.clear();

        // window.draw(...);
        if (currentState == GameState::Menu)

            menu.draw(window);

        else if (currentState == GameState::Playing)

            game.render(window);

        else if (currentState == GameState::Exiting)

            window.close();

        // ostatnia czynnosc - wyswietl okno wraz zawartoscia
        window.display();
    }

    return 0;
}