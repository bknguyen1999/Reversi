#include "grid.h"
#include "textdisplay.h"
#include "state.h"
using namespace std;

// helper function
/*void Grid::resetState(){
    for(size_t i = 0; i < gridSize; i++){
        for(size_t j = 0; j < gridSize; j++){
            State s; 
            s.type = StateType::Relay;
            s.colour = Colour::NoColour;
            s.direction = Direction::N;
            theGrid[i][j].setState(s);
        }
    }
}*/

void Grid::updateCount(){
    int num_black = 0;
    int num_white = 0;
    for (size_t i = 0; i < gridSize; i++){
        for (size_t j = 0; j < gridSize; j++){
            Info info = theGrid[i][j].getInfo();
            if(info.colour == Colour::Black){
                num_black++;
            }
            else if (info.colour == Colour::White){
                num_white++;
            }
        }
    }
    this->black = num_black;
    this->white = num_white;
}

/*void Grid::updateDisplay(){
    for(size_t i = 0; i < gridSize; i++){
        for(size_t j = 0; j < gridSize; j++){
            if(theGrid[i][j].colour == Colour::White){
                td->theDisplay[i][j] = 'W';
            }
            else if(theGrid[i][j].colour == Colour::Black){
                td->theDisplay[i][j] = 'B';
            }
            else if(theGrid[i][j].colour == Colour::NoColour){
                td->theDisplay[i][j] = '-';
            }
        }
    }
}*/


Grid::~Grid(){
    delete td;
    delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob){/*
    size_t i = ob->r;
    size_t j = ob->c;
    size_t n = gridSize;
    if(i == 0 && j == 0){
        theGrid[i][j].attach(&theGrid[i][j+1]);
        theGrid[i][j].attach(&theGrid[i+1][j]);
        theGrid[i][j].attach(&theGrid[i+1][j+1]);
    }
    else if(i == 0 && j == n-1){
        theGrid[i][j].attach(&theGrid[i][j-1]);
        theGrid[i][j].attach(&theGrid[i+1][j]);
        theGrid[i][j].attach(&theGrid[i+1][j-1]);
    }
    else if(i == n-1 && j == 0){
        theGrid[i][j].attach(&theGrid[i-1][j]);
        theGrid[i][j].attach(&theGrid[i-1][j+1]);
        theGrid[i][j].attach(&theGrid[i][j+1]);
    }
    else if(i == n-1 && j == n-1){
        theGrid[i][j].attach(&theGrid[i][j-1]);
        theGrid[i][j].attach(&theGrid[i-1][j]);
        theGrid[i][j].attach(&theGrid[i-1][j-1]);
    }
    else if(i == 0){
        theGrid[i][j].attach(&theGrid[i+1][j]);
        theGrid[i][j].attach(&theGrid[i+1][j+1]);
        theGrid[i][j].attach(&theGrid[i+1][j-1]);
        theGrid[i][j].attach(&theGrid[i][j-1]);
        theGrid[i][j].attach(&theGrid[i][j+1]);
    }
    else if(j == 0){
        theGrid[i][j].attach(&theGrid[i-1][j]);
        theGrid[i][j].attach(&theGrid[i+1][j]);
        theGrid[i][j].attach(&theGrid[i][j+1]);
        theGrid[i][j].attach(&theGrid[i-1][j+1]);
        theGrid[i][j].attach(&theGrid[i+1][j+1]);
    }
    else if(i == n-1){
        theGrid[i][j].attach(&theGrid[i-1][j]);
        theGrid[i][j].attach(&theGrid[i-1][j+1]);
        theGrid[i][j].attach(&theGrid[i-1][j-1]);
        theGrid[i][j].attach(&theGrid[i][j-1]);
        theGrid[i][j].attach(&theGrid[i][j+1]);
    }
    else if(j == n-1){
        theGrid[i][j].attach(&theGrid[i][j-1]);
        theGrid[i][j].attach(&theGrid[i-1][j]);
        theGrid[i][j].attach(&theGrid[i+1][j]);
        theGrid[i][j].attach(&theGrid[i+1][j-1]);
        theGrid[i][j].attach(&theGrid[i-1][j-1]);
    }
    else{
        theGrid[i][j].attach(&theGrid[i][j+1]);
        theGrid[i][j].attach(&theGrid[i][j-1]);
        theGrid[i][j].attach(&theGrid[i+1][j]);
        theGrid[i][j].attach(&theGrid[i-1][j]);
        theGrid[i][j].attach(&theGrid[i-1][j-1]);
        theGrid[i][j].attach(&theGrid[i-1][j+1]);
        theGrid[i][j].attach(&theGrid[i+1][j-1]);
        theGrid[i][j].attach(&theGrid[i+1][j+1]);
    }*/
}


bool Grid::isFull() const{
    return (black + white) == (gridSize * gridSize);
    /*for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            if (theGrid[i][j].colour == Colour::NoColour){
                return false;
            }
        }
    }
    return true;*/
}

Colour Grid::whoWon() const{
    if (black > white){
        return Colour::Black;
    }
    else if (black < white){
        return Colour::White;
    }
    else{
        return Colour::NoColour;
    }
}

void Grid::init(size_t n){
    if(td) {
        delete td;
        delete ob;
        theGrid.clear();
        black = 0;
        white = 0;
        gridSize = 0;
    }
    gridSize = n;
    int z =(int)((size_t)n);
    td = new TextDisplay{z};
    for(size_t i = 0; i < n; i++){
        vector<Cell> row;
        for(size_t j = 0; j < n; j++){
            Cell c{i,j};
            c.attach(td);
            row.emplace_back(c);
        }
        theGrid.emplace_back(row);
    }
    /*State b;
    b.type = StateType::Relay;
    b.colour = Colour::Black;
    State w;
    w.type = StateType::Relay;
    w.colour = Colour::White;*/
    setPiece(n/2 - 1, n/2 - 1, Colour::Black);
    //theGrid[n/2 - 1][n/2 - 1].setState(b);
    setPiece(n/2 - 1, n/2, Colour::White);
    //theGrid[n/2 - 1][n/2].setState(w);
    setPiece(n/2, n/2 - 1, Colour::White);
    //theGrid[n/2][n/2 - 1].setState(w);
    setPiece(n/2, n/2, Colour::Black);
    //theGrid[n/2][n/2].setState(b);
    /*for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            Info info = theGrid[i][j].getInfo();
            setObserver(info);
    }*/
    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            if(i == 0 && j == 0){
                theGrid[i][j].attach(&theGrid[i][j+1]);
                theGrid[i][j].attach(&theGrid[i+1][j]);
                theGrid[i][j].attach(&theGrid[i+1][j+1]);
            }
            else if(i == 0 && j == n-1){
                theGrid[i][j].attach(&theGrid[i][j-1]);
                theGrid[i][j].attach(&theGrid[i+1][j]);
                theGrid[i][j].attach(&theGrid[i+1][j-1]);
            }
            else if(i == n-1 && j == 0){
                theGrid[i][j].attach(&theGrid[i-1][j]);
                theGrid[i][j].attach(&theGrid[i-1][j+1]);
                theGrid[i][j].attach(&theGrid[i][j+1]);
            }
            else if(i == n-1 && j == n-1){
                theGrid[i][j].attach(&theGrid[i][j-1]);
                theGrid[i][j].attach(&theGrid[i-1][j]);
                theGrid[i][j].attach(&theGrid[i-1][j-1]);
            }
            else if(i == 0){
                theGrid[i][j].attach(&theGrid[i+1][j]);
                theGrid[i][j].attach(&theGrid[i+1][j+1]);
                theGrid[i][j].attach(&theGrid[i+1][j-1]);
                theGrid[i][j].attach(&theGrid[i][j-1]);
                theGrid[i][j].attach(&theGrid[i][j+1]);
            }
            else if(j == 0){
                theGrid[i][j].attach(&theGrid[i-1][j]);
                theGrid[i][j].attach(&theGrid[i+1][j]);
                theGrid[i][j].attach(&theGrid[i][j+1]);
                theGrid[i][j].attach(&theGrid[i-1][j+1]);
                theGrid[i][j].attach(&theGrid[i+1][j+1]);
            }
            else if(i == n-1){
                theGrid[i][j].attach(&theGrid[i-1][j]);
                theGrid[i][j].attach(&theGrid[i-1][j+1]);
                theGrid[i][j].attach(&theGrid[i-1][j-1]);
                theGrid[i][j].attach(&theGrid[i][j-1]);
                theGrid[i][j].attach(&theGrid[i][j+1]);
            }
            else if(j == n-1){
                theGrid[i][j].attach(&theGrid[i][j-1]);
                theGrid[i][j].attach(&theGrid[i-1][j]);
                theGrid[i][j].attach(&theGrid[i+1][j]);
                theGrid[i][j].attach(&theGrid[i+1][j-1]);
                theGrid[i][j].attach(&theGrid[i-1][j-1]);
            }
            else{
                theGrid[i][j].attach(&theGrid[i][j+1]);
                theGrid[i][j].attach(&theGrid[i][j-1]);
                theGrid[i][j].attach(&theGrid[i+1][j]);
                theGrid[i][j].attach(&theGrid[i-1][j]);
                theGrid[i][j].attach(&theGrid[i-1][j-1]);
                theGrid[i][j].attach(&theGrid[i-1][j+1]);
                theGrid[i][j].attach(&theGrid[i+1][j-1]);
                theGrid[i][j].attach(&theGrid[i+1][j+1]);
            }
            //theGrid[i][j].notifyObservers();
        }
    }
    updateCount();
    // set ob
}

void Grid::setPiece(size_t r, size_t c, Colour colour){
    //Info i = theGrid[r][c].getInfo();
    if (r >= gridSize || r < 0 || c >= gridSize || c < 0){
        throw InvalidMove{};
        //return;
    }
    theGrid[r][c].setPiece(colour);
    theGrid[r][c].notifyObservers();
    updateCount();
    //resetState();
    //updateDisplay();
}

void Grid::toggle(size_t r, size_t c){
    theGrid[r][c].toggle(); 
}

ostream& operator<<(std::ostream &out, const Grid &g){
    out << *(g.td);
    return out;
}



