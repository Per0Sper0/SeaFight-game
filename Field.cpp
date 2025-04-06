#include "Field.h"

Field::Field() {
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      field[i][j].symbol = 'o';
    }
  }
  for (int i = 1; i <= 10; i++) {
    field[i][0].symbol = char('A' + i - 1);
    field[i][11].symbol = char('A' + i - 1);
  }
  for (int j = 1; j <= 10; j++) {
    field[0][j].symbol = char(48 + j - 1);
    field[11][j].symbol = char(48 + j - 1);
  }
}
void Field::PutShip(int shipnum, int rotate, int x, int y, int& count) {
  int flag = 1;
  if (rotate == 0) {
    for (int j = 0; j < shipnum; j++) {
      if (field[x][y + j].symbol == 'n' || field[x][y + j].symbol == 'k') {
        flag = 0;
      }
    }
    if (flag) {
      for (int j = 0; j < shipnum; j++) {
        field[x][y + j].symbol = 'k';
      }
      for (int t = 0; t < shipnum; t++) {
        for (int k = -1; k <= 1; k++) {
          for (int l = -1; l <= 1; l++) {
            if (field[x + k][y + t + l].symbol == 'o') {
              field[x + k][y + t + l].symbol = 'n';
            }
          }
        }
      }
      count++;
    }
  }
  if (rotate == 1) {
    for (int i = 0; i < shipnum; i++) {
      if (field[x + i][y].symbol == 'n' || field[x + i][y].symbol == 'k') {
        flag = 0;
      }
    }
    if (flag) {
      for (int i = 0; i < shipnum; i++) {
        field[x + i][y].symbol = 'k';
      }
      for (int t = 0; t < shipnum; t++) {
        for (int k = -1; k <= 1; k++) {
          for (int l = -1; l <= 1; l++) {
            if (field[x + k + t][y + l].symbol == 'o') {
              field[x + k + t][y + l].symbol = 'n';
            }
          }
        }
      }
      count++;
    }
  }
}
