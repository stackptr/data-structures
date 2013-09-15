/* board.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Defines the Board class interface.
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>

namespace TileState {
enum TileState { Blank = ' ', X = 'X', O = 'O', Invalid = '?'};
}

class Board {
public:
  Board(int, int);
  TileState::TileState& operator[](const int);
  TileState::TileState& operator[](const std::vector<int>);
  void draw();

private:
  int width; // Width of one row (n)
  int size;  // n x n size of the board
  int match; // Size that determines a win
  std::vector<TileState::TileState> data;
};
#endif