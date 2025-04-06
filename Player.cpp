#include "Player.h"

Player::Player(int num) {
  withouttex.loadFromFile("asserts/withoutship.jpg");
  shiptex.loadFromFile("asserts/ship1.jpg");
  misstex.loadFromFile("asserts/mimo.jpg");
  killedtex.loadFromFile("asserts/killed.jpg");
  chosentex.loadFromFile("asserts/chosen.jpg");
  number = num;
}
void Player::DrawField(sf::RenderWindow& window, Field& quefield) {
  window.clear(sf::Color::White);
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 11; j++) {
      if (quefield.field[i][j].symbol == 'o' || quefield.field[i][j].symbol == 'n') {
        sprite.setTexture(withouttex);
      }
      if (quefield.field[i][j].symbol == 'k') {
        sprite.setTexture(shiptex);
      }
      if (quefield.field[i][j].symbol == '*') {
        sprite.setTexture(misstex);
      }
      if (quefield.field[i][j].symbol == 'x') {
        sprite.setTexture(killedtex);
      }
      if (i == 0 || j == 0) {
        continue;
      }
      sprite.setPosition(j * 44, i * 36);
      window.draw(sprite);
    }
  }
}
void Player::Hit(Player& other, int i, int j, int& flag) {
  sf::sleep(sf::milliseconds(500));
  if (other.my_field.field[i][j].symbol == 'k') {
    op_field.field[i][j].symbol = 'x';
    other.my_field.field[i][j].symbol = 'x';
    int boflag = 1;
    for (int k = -1; k <= 1; k++) {
      for (int l = -1; l <= 1; l++) {
        if (other.my_field.field[i - k][j - l].symbol == 'k') {
          boflag = 0;
        }
      }
    }
    if (boflag) {
      int t = 0;
      while (other.my_field.field[i - t][j].symbol == 'x') {
        for (int l = -1; l <= 1; l++) {
          for (int k = -1; k <= 1; k++) {
            if (other.my_field.field[i - t + l][j + k].symbol == 'o' || other.my_field.field[i - t + l][j + k].symbol == 'n') {
              other.my_field.field[i - t + l][j + k].symbol = '*';
              op_field.field[i - t + l][j + k].symbol = '*';
            }
          }
        }
        t++;
      }
      t = 0;
      while (other.my_field.field[i + t][j].symbol == 'x') {
        for (int l = -1; l <= 1; l++) {
          for (int k = -1; k <= 1; k++) {
            if (other.my_field.field[i + t + l][j + k].symbol == 'o' || other.my_field.field[i + t + l][j + k].symbol == 'n') {
              other.my_field.field[i + t + l][j + k].symbol = '*';
              op_field.field[i + t + l][j + k].symbol = '*';
            }
          }
        }
        t++;
      }
      t = 0;
      while (other.my_field.field[i][j - t].symbol == 'x') {
        for (int l = -1; l <= 1; l++) {
          for (int k = -1; k <= 1; k++) {
            if (other.my_field.field[i + l][j + k - t].symbol == 'o' || other.my_field.field[i + l][j + k - t].symbol == 'n') {
              other.my_field.field[i + l][j + k - t].symbol = '*';
              op_field.field[i + l][j + k - t].symbol = '*';
            }
          }
        }
        t++;
      }
      while (other.my_field.field[i][j + t].symbol == 'x') {
        for (int l = -1; l <= 1; l++) {
          for (int k = -1; k <= 1; k++) {
            if (other.my_field.field[i + l][j + k + t].symbol == 'o' || other.my_field.field[i + l][j + k + t].symbol == 'n') {
              other.my_field.field[i + l][j + k + t].symbol = '*';
              op_field.field[i + l][j + k + t].symbol = '*';
            }
          }
        }
        t++;
      }
    }
    other.counter--;
    flag = number;
  }
  if (other.my_field.field[i][j].symbol == 'o' || other.my_field.field[i][j].symbol == 'n') {
    op_field.field[i][j].symbol = '*';
    other.my_field.field[i][j].symbol = '*';
    flag = other.number;
  }
}
void Player::Fill() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "Sea battle");
  window.setKeyRepeatEnabled(false);
  sf::Vector2i localPosition = sf::Mouse::getPosition(window);
  if (number == 1) {
    text.loadFromFile("asserts/stay1.jpg");
  } else {
    text.loadFromFile("asserts/stay2.jpg");
  }
  textsprite.setTexture(text);
  int rotate = 0;
  int count = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    DrawField(window, my_field);
    window.draw(textsprite);
    localPosition = sf::Mouse::getPosition(window);
    if (localPosition.x / 44 > 0 && localPosition.y / 36 > 0) {
      if (count <= 4) {
        if (count == 4) {
          count++;
        }
        if (localPosition.x / 44 < 11 && localPosition.y / 36 < 11) {
          sprite.setTexture(shiptex);
          sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
          window.draw(sprite);
          int i = localPosition.y / 36;
          int j = localPosition.x / 44;
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            my_field.PutShip(1, 1, i, j, count);
            sf::sleep(sf::milliseconds(150));
          }
        }
      }
      if (count >= 5 && count <= 7) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          rotate = (rotate + 1) % 2;
          sf::sleep(sf::milliseconds(150));
        }
        if (rotate == 0) {
          if (localPosition.x / 44 < 10 && localPosition.y / 36 < 11) {
            sprite.setTexture(shiptex);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44 + 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            int i = localPosition.y / 36;
            int j = localPosition.x / 44;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              my_field.PutShip(2, 0, i, j, count);
              sf::sleep(sf::milliseconds(150));
            }
          }
        }
        if (rotate == 1) {
          if (localPosition.x / 44 < 11 && localPosition.y / 36 < 10) {
            sprite.setTexture(shiptex);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36 + 36);
            window.draw(sprite);
            int i = localPosition.y / 36;
            int j = localPosition.x / 44;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              my_field.PutShip(2, 1, i, j, count);
              sf::sleep(sf::milliseconds(150));
            }
          }
        }
        if (count == 8) {
          count++;
        }
      }
      if (count >= 9 && count <= 10) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          rotate = (rotate + 1) % 2;
          sf::sleep(sf::milliseconds(150));
        }
        if (rotate == 0) {
          if (localPosition.x / 44 < 9 && localPosition.y / 36 < 11) {
            sprite.setTexture(shiptex);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44 + 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44 + 44 * 2, (localPosition.y / 36) * 36);
            window.draw(sprite);
            int i = localPosition.y / 36;
            int j = localPosition.x / 44;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              my_field.PutShip(3, 0, i, j, count);
              sf::sleep(sf::milliseconds(150));
            }
          }
        }
        if (rotate == 1) {
          if (localPosition.x / 44 < 11 && localPosition.y / 36 < 9) {
            sprite.setTexture(shiptex);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36 + 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36 + 36 * 2);
            window.draw(sprite);
            int i = localPosition.y / 36;
            int j = localPosition.x / 44;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              my_field.PutShip(3, 1, i, j, count);
              sf::sleep(sf::milliseconds(150));
            }
          }
        }
        if (count == 11) {
          count++;
        }
      }
      if (count == 12) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          rotate = (rotate + 1) % 2;
          sf::sleep(sf::milliseconds(150));
        }
        if (rotate == 0) {
          if (localPosition.x / 44 < 8 && localPosition.y / 36 < 11) {
            sprite.setTexture(shiptex);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44 + 44 * 3, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44 + 44 * 2, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44 + 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            int i = localPosition.y / 36;
            int j = localPosition.x / 44;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              my_field.PutShip(4, 0, i, j, count);
              sf::sleep(sf::milliseconds(150));
            }
          }
        }
        if (rotate == 1) {
          if (localPosition.x / 44 < 11 && localPosition.y / 36 < 8) {
            sprite.setTexture(shiptex);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36 + 36 * 3);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36 + 36 * 2);
            window.draw(sprite);
            sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36 + 36 * 1);
            window.draw(sprite);
            int i = localPosition.y / 36;
            int j = localPosition.x / 44;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              my_field.PutShip(4, 1, i, j, count);
              sf::sleep(sf::milliseconds(150));
            }
          }
        }
      }
    }
    window.display();
    if (count == 13) {
      window.close();
    }
  }
}
void Player::Fight(Player& other, sf::RenderWindow& window, int& flag, sf::Event& event) {
  sf::Vector2i localPosition = sf::Mouse::getPosition(window);
  if (number == 1) {
    text.loadFromFile("asserts/fight1.jpg");
  } else {
    text.loadFromFile("asserts/fight2.jpg");
  }
  textsprite.setTexture(text);
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }
  DrawField(window, op_field);
  window.draw(textsprite);
  localPosition = sf::Mouse::getPosition(window);
  if (localPosition.x / 44 < 11 && localPosition.y / 36 < 11 && localPosition.y / 36 > 0 && localPosition.x / 44 > 0) {
    sprite.setTexture(chosentex);
    sprite.setPosition((localPosition.x / 44) * 44, (localPosition.y / 36) * 36);
    window.draw(sprite);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      localPosition = sf::Mouse::getPosition(window);
      int i = localPosition.y / 36;
      int j = localPosition.x / 44;
      Hit(other, i, j, flag);
    }
  }
  if (other.counter == 0) {
    victory = true;
  }
  window.display();
}