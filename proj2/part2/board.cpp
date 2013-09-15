/* board.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Implements Board class.
 */

#include "board.h"
#include <iostream>

Board::Board(int n, int m): width(n), size(n*n), match(m){
  data.assign(size, TileState::Blank);
}

// Given a position, return the state of the tile
TileState::TileState& Board::operator[] (const int n){
  if (n < size)
    return data[n];
  else
    return TileState::Invalid;
}

// Given a position, return the state of the tile
// Vector v is an integer pair x and y
TileState::TileState& Board::operator[] (const std::vector<int> v){
  if (v[0] < width && v[1] < width)
    return data[v[0]*width + v[1]];
  else
    return TileState::Invalid;
}

void Board::draw(){
  for(int i=0; i < width; i++){ // Row
    for(int j=0; j<width; j++){ // Column
      std::cout << " " << data[i*width + j];
      if (j != width-1) // End of column
        std::cout << " |";
    }
    // Draw divider between rows
    if (i != width-1){ // Except for last row
    std::cout << std::endl;
    for (int j=0; j<width; j++){
      if(j != width-1)
        std::cout << "---+";
      else
        std::cout << "---\n";
    }
    }
    else
      std::cout << std::endl;
  }
}