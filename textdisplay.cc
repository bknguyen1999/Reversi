#include "textdisplay.h"
#include <vector>
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n}{
    for(int i = 0; i < n; i++){
        vector<char> row;
        for(int j = 0; j < n; j++){
            char c;
            if((i == n/2 - 1) && (j == n/2 - 1)){
                c = 'B';
            }
            else if((i == n/2 - 1) && (j == n/2)){
                c = 'W';
            }
            else if((i == n/2) && (j == n/2 - 1)){
                c = 'W';
            }
            else if((i == n/2) && (j == n/2)){
                c = 'B';
            }
            else{
                c = '-';
            }
            row.emplace_back(c);
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
    Info info = whoNotified.getInfo();
    if(info.colour == Colour::Black){
        theDisplay[info.row][info.col] = 'B';
    }
    else if(info.colour == Colour::White){
        theDisplay[info.row][info.col] = 'W';
    }
    else{
        theDisplay[info.row][info.col] = '-';
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td){
    for(int i = 0; i < td.gridSize; i++){
        for(int j = 0; j < td.gridSize; j++){
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}
