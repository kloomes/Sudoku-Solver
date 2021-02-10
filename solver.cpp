#include <iostream>
#include <vector>

std::vector<std::vector<int>> grid = {
  {0, 6, 0, 0, 0, 2, 8, 9, 0}, //00, 01, 02 etc
  {0, 4, 0, 6, 0, 0, 0, 1, 5}, //10, 11, 12 etc
  {0, 0, 0, 0, 1, 0, 2, 0, 0},
  {0, 0, 8, 0, 0, 6, 0, 0, 0},
  {0, 0, 0, 4, 0, 7, 0, 0, 0},
  {0, 0, 0, 9, 0, 0, 6, 0, 0},
  {0, 0, 9, 0, 4, 0, 0, 0, 0},
  {8, 2, 0, 0, 0, 1, 0, 5, 0},
  {0, 1, 7, 8, 0, 0, 0, 4, 0} //90, 91, 92 etc
};

std::vector<int> assignSquare(int row, int col) {
  std::vector<int> square;
  if (row >= 0 && row <= 2) square.push_back(0);
  if (row >= 3 && row <= 5) square.push_back(3);
  if (row >= 6 && row <= 8) square.push_back(6);
  if (col >= 0 && col <= 2) square.push_back(0);
  if (col >= 3 && col <= 5) square.push_back(3);
  if (col >= 6 && col <= 8) square.push_back(6);
  return square;
}

bool checkRow(int num, int row) {
  for (int i = 0; i <= 8; i++)
    if (num == grid[row][i]) return false;
  return true;
}

bool checkCol(int num, int col) {
  for (int i = 0; i <= 8; i++)
    if (num == grid[i][col]) return false;
  return true;
}

bool checkSquare(int num, int rowStart, int colStart) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (num == grid[rowStart + i][colStart + j]) return false;
    }
  }
  return true;
}

bool checkValid(int num, int row, int col) {
  std::vector<int> square = assignSquare(row, col);
  if (!checkRow(num, row) || !checkCol(num, col) || !checkSquare(num, square[0], square[1])) return false;
  return true;
}

bool complete() {
  for (int row = 0; row <= 8; row++)
    for (int col = 0; col <= 8; col++) {
      if (grid[row][col] == 0) return false;
    }
    return true;
}

std::vector<int> assignParams() {
  std::vector<int> params;
  for (int row = 0; row <= 8; row++)
    for (int col = 0; col <= 8; col++) {
      if (grid[row][col] == 0) {
        params.push_back(row);
        params.push_back(col);
        return params;
      }
    }
    return {0, 0};
}

bool solve() {
  int row, col;
  std::vector<int> params = assignParams();
  row = params[0];
  col = params[1];
  if (complete()) return true;
  for (int num = 1; num <= 9; num++) {
    if (checkValid(num, row, col)) {
      grid[row][col] = num;
      if (solve()) return true;
      grid[row][col] = 0;
    }
  }
  return false;
}
void printGrid() {
  for (int row = 0; row <= 8; row++) {
    for (int col = 0; col <= 8; col++) {
      std::cout << grid[row][col];
      if (col == 8) std::cout << "\n";
    }
  }
}

int main() {
  solve();
  printGrid();
}
