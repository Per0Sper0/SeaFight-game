#include <SFML/Graphics.hpp>

#include "Player.h"


int main() {
  Player player1(1), player2(2);
  player1.Fill();
  player2.Fill();
  sf::RenderWindow window(sf::VideoMode(800, 800), "Sea battle");
  sf::Texture text;
  sf::Sprite textsprite;
  int flag = 1;
  while (window.isOpen()) {
    sf::Event event;
    if (flag == 1 && !player1.victory && !player2.victory) {
      player1.Fight(player2, window, flag, event);
    }
    if (flag == 2 && !player1.victory && !player2.victory) {
      player2.Fight(player1, window, flag, event);
    }
    if (player1.victory || player2.victory) {
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
      }
      if (player1.victory) {
        text.loadFromFile("asserts/victory1.jpg");
      } else {
        text.loadFromFile("asserts/victory2.jpg");
      }
      textsprite.setTexture(text);
      window.clear(sf::Color::White);
      window.draw(textsprite);
      window.display();
    }
  }

  return 0;
}