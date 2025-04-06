#pragma once

#include "Ship.h"

struct Cell {
  Ship* ship;
  char symbol;
};
struct Field {
  int shipcount_ = 10;
  // x - строки
  // y - cтолбцы
  // пустые поля o
  // корабли k
  // подбитые корабли x
  // место куда нкльзя поставить корабль n
  Cell field[15][15];
  Field();
  void PutShip(int shipnum, int rotate, int x, int y, int& count);
};