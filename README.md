# Gra_typu_arkanoid

Prosta gra 2D zbudowana na bibliotece **SFML**, w której poruszasz paletką, aby odbijać piłkę i niszczyć rzędy kolorowych bloków.

## Sterowanie
- **A / ←** – ruch paletki w lewo.
- **D / →** – ruch paletki w prawo.
- **Enter** – wybór opcji w menu głównym.
- **Escape** – powrót z ekranu wyników do menu.
- Zamknięcie okna kończy działanie programu.
- Po kliknieciu **T w menu słońce zaczyna się ruszać

## Tryby i menu
Po uruchomieniu aplikacji pojawia się menu z trzema pozycjami:
1. **Nowa gra** – start rozgrywki.
2. **Ostatnie wyniki** – podgląd do pięciu ostatnich gier wraz z informacją o wygranej/przegranej i czasem trwania.
3. **Wyjście** – zamknięcie gry.

## Zasady gry
- Paletka znajduje się przy dolnej krawędzi ekranu i porusza się z prędkością 400 pikseli na sekundę.
- Piłka startuje w środkowej części planszy z domyślną prędkością i odbija się od ścian oraz paletki.
- Na górze planszy ułożone jest 8 kolumn bloków w 10 rzędach. Bloki mają różną wytrzymałość (od 1 do 3 punktów życia) zależną od wiersza i zmieniają kolor po każdym trafieniu.
- Trafienie piłką w blok zmniejsza jego punkty życia; po spadku do zera blok znika.
- Przegrywasz, gdy piłka spadnie poniżej dolnej krawędzi planszy.
- Wygrywasz, gdy zniszczysz wszystkie bloki.

## Wyniki
Po zakończeniu partii gra wraca do menu. Ostatnie wyniki (maksymalnie pięć) można obejrzeć w sekcji **Ostatnie wyniki** – wyświetla się status wygranej/przegranej oraz czas rozgrywki w sekundach.


