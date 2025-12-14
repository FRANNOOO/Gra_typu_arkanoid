//
// Created by bonfr on 15.11.2025.
//
#include <SFML/Graphics.hpp>
#include <array> // Użyjemy std::array zamiast std::vector
#ifndef SFML_STONE_H
#define SFML_STONE_H


class Stone : public sf::RectangleShape
{
   public:
   Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
   void trafienie();
   void aktualizujKolor();
   bool isDestroyed() const;
   void draw(sf::RenderTarget &target) const;
   int getHP() const { return m_punktyZycia; };


   private:
   int m_punktyZycia;
   bool m_jestZniszczony;
   inline static std::array<sf::Color, 4> m_colorLUT = {
      sf::Color::Transparent, // L = 0
      sf::Color::Red,         // L = 1
      sf::Color::Yellow,      // L = 2
      sf::Color::Blue         // L = 3
   };
};

#endif //SFML_STONE_H