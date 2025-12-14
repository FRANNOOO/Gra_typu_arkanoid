#include "Stone.h"
#include <SFML/Graphics.hpp>
#include <array>

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
: sf::RectangleShape(rozmiar)      // ustawiamy rozmiar w konstruktorze bazowym
, m_punktyZycia(L)
, m_jestZniszczony(false)
{
   this->setPosition(startPos);
   this->setOutlineThickness(2.f); // obrys
   this->setOutlineColor(sf::Color::Black);
   aktualizujKolor();              //kolor startowy
}

// Trafienie w blok
void Stone::trafienie()
{
   // Jeśli już zniszczony – nic nie rób
   if (m_jestZniszczony)
      return;

   // Zmniejszamy HP
   --m_punktyZycia;

   // Aktualizujemy kolor po trafieniu
   aktualizujKolor();

   // Jeśli HP <= 0, oznaczamy jako zniszczony
   if (m_punktyZycia <= 0)
   {
      m_jestZniszczony = true;
   }
}

// Aktualizacja koloru na podstawie liczby punktów życia
void Stone::aktualizujKolor()
{
   // Zabezpieczenie przed wyjściem poza zakres tablicy
   if (m_punktyZycia <= 0)
   {
      // L <= 0 → indeks 0 (Transparent)
      this->setFillColor(m_colorLUT[0]);
   }
   else if (static_cast<std::size_t>(m_punktyZycia) < m_colorLUT.size())
   {
      // L w [1, 3]
      this->setFillColor(m_colorLUT[static_cast<std::size_t>(m_punktyZycia)]);
   }
   else
   {
      // Gdyby ktoś dał L > 3, użyjemy ostatniego koloru
      this->setFillColor(m_colorLUT.back());
   }
}

// Getter: czy blok jest zniszczony
bool Stone::isDestroyed() const
{
   return m_jestZniszczony;
}

// Rysujemy blok tylko, jeśli nie jest zniszczony
void Stone::draw(sf::RenderTarget& target) const
{
   if (!m_jestZniszczony)
   {
      target.draw(*this); // Stone dziedziczy po RectangleShape
   }
}