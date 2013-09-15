/* main.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Plays a game of tic-tac-toe against a computer. Uses recursive evaluation
 * of game trees to move.
 */

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

// Function declarations
void clearScrn();                // Prints a lot of new lines to "clear" screen
void drawBoard(char*);           // Draw current state of board
char boardWin(char*, int);       // Evaluate if board is in won state
int minimax(char, char*, int);   // The source of all frustration in this assignment
int alpha_beta(char, char*, int, int, int);

// Variables
int n = 0;
int m = 0;
int turn = 0;
int move = -1;

int main(int argc, char** argv){
  // Process arguments
  if(argc < 4 || argc > 4){
    std::cout << "Invalid arguments:\n./proj2 <n> <m> <h|c>\n";
    return 1;
  }
  
  if (strlen(argv[1]) >= 2)     // Handle max n = 10
    n = 10;
  else
    n = argv[1][0] - 0x30;      // n x n board
  m = argv[2][0] - 0x30;        // m marks in a line to win
  char turn = *argv[3];       // 'h' for human's turn, 'c' for computer's turn

  // Set pieces
  char humanPiece, compPiece;
  if(turn == 'h'){
    // Human goes first
    humanPiece = 'X';
    compPiece = 'O';
  }
  else {
    humanPiece = 'O';
    compPiece = 'X';
  }

  // Create the board
  char board[n*n];
  // Blank all cells
  for(int i = 0; i < n*n; i++)
    board[i] = ' ';

  // Print instructions and blank board
  std::cout << "Enter a coordinate from 1 to " << n << " in the form: x y\n\n";
  drawBoard(board);

  // Start game loop
  int movex = 0;
  int movey = 0;
  char status;
  while(true){
    if(turn == 'h'){
      std::cout << "> ";
      std::cin >> movex >> movey;
      move = ((movex-1) * n) + (movey-1);
      board[move] = humanPiece;
      turn = 'c';
    }
    else if(turn == 'c'){
      clearScrn(); // Clear screen
      minimax(compPiece, board, move);
      drawBoard(board);
      turn = 'h';
    }
    // After making a move, evaluate the board
    status = boardWin(board, move);
    if(status != '0')
      break;
  }
  // Print ending game message
  clearScrn();
  drawBoard(board);
  if ( status == humanPiece)
    std::cout << "Human player won!\n";
  else if (status == compPiece)
    std::cout << "Computer won!\n";
  else
    std::cout << "Draw!\n";
  return 0;
}

int minimax(char player, char* board, int p){
  std::cout << "Minimax called: player=" << player << " p=" << p << "\n";
  // First check if board is won
  char state = boardWin(board, p);
  if (state == 'X')
    return 1;
  if (state == 'O')
    return -1;
  if (state == 'D')
    return 0;

  // Get a list of all legal moves for player
  std::vector<int> moves;
  char temp_board[n*n];
  for(int i = 0; i < n*n; i++){
    temp_board[i] = board[i];
    if(board[i] == ' '){
      std::cout << "Legal move: " << i << std::endl;
      moves.push_back(i);
    }
  }

  int result;
  int current;
  if (player == 'X'){ // MAX
    result = -99;
    for(std::vector<int>::iterator it = moves.begin(); it != moves.end(); it++){
      temp_board[*it] = 'X';
      current = minimax('O', temp_board, *it);
      if (result < current){
        result = current;
        std::cout << "MAX result changed: " << result << "\n";
        move = *it;
      }
    }
    board[move] = 'X';
  }
  if (player == 'O'){ // MIN
    result = 99;
    for(std::vector<int>::iterator it = moves.begin(); it != moves.end(); it++){
      temp_board[*it] = 'O';
      current = minimax('X', temp_board, *it);
      if (result > current){
        result = current;
        std::cout << "MIN result changed: " << result << "\n";
        move = *it;
      }
    }
    board[move] = 'O';
  }
  return result;
}

/* boardWin
 *
 * Given a board state and the last move p, evaluate if the board is in a won state
 * Returns X, O if winner; D if drawn; 0 if no winner and not drawn
 */
char boardWin(char* board, int p){
  // Pass -1 for a blank board state
  if (p < 0)
    return 0;

  // Determine pieces to check
  char piece = board[p];

  // First see if there is a vertical win
  int match = 0;
  for(int i = p; i-n >= 0; i -= n){ // Look above the position
    if(board[i] == board[i-n]){
      //std::cout << "1) Match at: " << i << " " << i-n << "\n";
      match++;
    }
    else
      break;
  }
  for(int i = p; i+n < n*n; i += n){ // Look below the position
    if(board[i] == board[i+n]){
      //std::cout << "2) Match at: " << i << " " << i+n << "\n";
      match++;
    }
    else
      break;
  }
  if (match >= m-1)
    return piece;

  // No vertical win, proceed to horizontal check
  match = 0; // Reset match counter
  for(int i = p; i > p - (p%n); i--){ // Look to the left
    if(board[i] == board[i-1]){
      //std::cout << "3) Match at: " << i << " " << i-1 << "\n";
      match++;
    }
    else
      break;
  }
  for(int i = p; i < (p+n) - (p%n) - 1; i++){ // Look to the right
    if(board[i] == board[i+1]){
      //std::cout << "4) Match at: " << i << " " << i+1<< "\n";
      match++;
    }
    else
      break;
  }
  if (match >= m-1)
    return piece;

  // Check for a diagonal win
  match = 0;
  for(int i = p; i < (n*n) - n - 1; i += n+1){ // Look south-east
    if(board[i] == board[i+n+1] && (i+1)%n != 0){
      //std::cout << "5) Match at: " << i << " " << i+n+1<< "\n";
      match++;
    }
    else
      break;
  }
  for(int i = p; i > n; i = (i-n)-1){
    if(board[i] == board[i-n-1] && i%n != 0){ // Look north-west
      //std::cout << "6) Match at: " << i << " " << i-n-1<< "\n";
      match++;
    }
    else
      break;
  }
  if (match >= m-1)
    return piece;

  // Check for other diagonal
  match = 0;
  for(int i = p; i < (n*n)-n; i += (n-1)){ // Look south-west
    if(board[i] == board[i+n-1] && i%n != 0){
      //std::cout << "7) Match at: " << i << " " << i+n-1<< "\n";
      match++;
    }
    else
      break;
  }
  for(int i = p; i > n; i -= (n+1)){ // Look north-east
    if(board[i] == board[i-n+1] && (i+1)%n != 0){
      //std::cout << "8) Match at: " << i << " " << i-n+1<< "\n";
      match++;
    }
    else
      break;
  }
  if (match >= m-1)
    return piece;

  // Check if the board is drawn
  bool drawn = true;
  for(int i = 0; i < n*n; i++){
    if(board[i] == ' ')
      drawn = false;
  }
  if (drawn)
    return 'D';

  // No match found
  return '0';
}

void drawBoard(char* board){
  for(int i=0; i < n; i++){ // Row
    for(int j=0; j<n; j++){ // Column
      std::cout << " " << board[i*n + j];
      if (j != n-1) // End of column
        std::cout << " |";
    }
    // Draw divider between rows
    if (i != n-1){ // Except for last row
    std::cout << std::endl;
    for (int j=0; j<n; j++){
      if(j != n-1)
        std::cout << "---+";
      else
        std::cout << "---\n";
    }
    }
    else
      std::cout << std::endl;
  }
}

void clearScrn(){
  for(int i = 0; i < 40; i++)
    std::cout << "\n";
}