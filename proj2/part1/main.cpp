/* main.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Provides recursive function to implement:
 * f(N) = 0, if N < N1
 * f(N1) = C1
 * f(N)= A1 + M1*f(M2*N/D1 - S1) Op M3*f(M4*N/D2 - S2), if N > N1
 *
 * Expected command: ./recurse N1 C1 A1 M1 M2 M3 M4 D1 D2 S1 S2 Arg Op
 */

#include <iostream>
#include <cstring>
#include <cmath>

#define DEBUG 0
#define ARG_SIZE 12

// Some aliasing to make recursion function easier to read...
#define N1 args[0]
#define C1 args[1]
#define A1 args[2]
#define M1 args[3]
#define M2 args[4]
#define M3 args[5]
#define M4 args[6]
#define D1 args[7]
#define D2 args[8]
#define S1 args[9]
#define S2 args[10]
#define Arg args[11]

int args[ARG_SIZE] = {0};
char op;

int recurse(int N){
  if ( N < N1 )
    return 0;
  if ( N == N1 )
    return C1;
  if ( op == '-')
    return A1 + M1*recurse(M2*N/D1 - S1) - M3*recurse(M4*N/D2 - S2);
  return A1 + M1*recurse(M2*N/D1 - S1) + M3*recurse(M4*N/D2 - S2);
}

int main(int argc, char** argv){
  // Process arguments
  for (int i = 1; i < argc-1; i++)
    for(int j = 0; j < strlen(argv[i]); j++)
      args[i-1] += (*(argv[i]+j) - 0x30) * (int)pow(10,(strlen(argv[i]) - (j+1)));
  op = *argv[argc-1];

  if(DEBUG){
  std::cout << "Arguments: ";
  for (int i = 0; i < ARG_SIZE; i++){
    std::cout << args[i] << " ";
  }
  std::cout << op << std::endl;
  }

  std::cout << recurse(Arg) << std::endl;

}