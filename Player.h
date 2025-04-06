#pragma once
#include <SFML/Graphics.hpp>

#include "Field.h"
class Player {
 public:
  bool victory = false;
  Field my_field;
  Field op_field;
  int number;
  sf::Texture withouttex;
  sf::Texture shiptex;
  sf::Texture misstex;
  sf::Texture killedtex;
  sf::Texture chosentex;
  sf::Sprite sprite;
  sf::Texture text;
  sf::Sprite textsprite;
  int counter = 20;
  bool isMove = false;
  Player(int num);
  void DrawField(sf::RenderWindow& window, Field& quefield);
  void Hit(Player& other, int i, int j, int& flag);

  void Fill();
  void Fight(Player& other, sf::RenderWindow& window, int& flag, sf::Event& event);
};