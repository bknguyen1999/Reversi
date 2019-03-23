#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here

  try {
    int turn = 0;
    while (true) {
      cin >> cmd;
      if (cmd == "new") {
        int n;
        cin >> n;
        // Add code here
        g.init(n);
        cout << g;
      }
      else if (cmd == "play") {
        int r = 0, c = 0;
        cin >> r >> c;
        // Add code here
        try{
          if(turn % 2 == 0){
            g.setPiece(r,c, Colour::Black);
          }
          else{
            g.setPiece(r,c,Colour::White);
          }
          turn++;
        }
        catch(InvalidMove){
          continue;
        }
        if(g.isFull()){
          Colour winner = g.whoWon();
          if (winner == Colour::Black){
            cout << "Black Wins!" << endl;
          }
          else if(winner == Colour::White){
            cout << "White Wins!" << endl;
          }
          else{
            cout << "Tie!" << endl;
          }
          break;
        }
        if(cin.fail() || cin.eof()){
          break;
        }
        cout << g;
      }
    }
  }
  catch (ios::failure &f) {}  // Any I/O failure quits
}
