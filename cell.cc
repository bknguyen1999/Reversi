#include "cell.h"
#include <iostream>
#include "grid.h"
using namespace std;

Direction Cell::oppositeDir(Direction dir){
    if(dir == Direction::N){
        return Direction::S;
    }
    else if(dir == Direction::S){
        return Direction::N;
    }
    else if(dir == Direction::W){
        return Direction::E;
    }
    else if(dir == Direction::E){
        return Direction::W;
    }
    else if(dir == Direction::SW){
        return Direction::NE;
    }
    else if(dir == Direction::SE){
        return Direction::NW;
    }
    else if(dir == Direction::NE){
        return Direction::SW;
    }
    else {
        return Direction::SE;
    }
}


Cell::Cell(size_t r, size_t c):r{r}, c{c}, has_piece{false}{}


void Cell::setPiece(Colour colour){
    if (!has_piece){
        this->colour = colour;
        this->has_piece = true;
        State s{StateType::NewPiece, colour, Direction::N};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::NE};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::E};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::SE};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::S};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::SW};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::W};
        this->setState(s);
        this->notifyObservers();
        s = {StateType::NewPiece, colour, Direction::NW};
        this->setState(s);
        this->notifyObservers();
    }
    else{
        throw InvalidMove{};
    }
}

void Cell::toggle(){
    if(this->colour == Colour::Black){
        this->colour = Colour::White;
    }
    else{
        this->colour = Colour::Black;
    }
}

void Cell::notify(Subject<Info, State> &whoFrom){
    Info srcInfo = whoFrom.getInfo();
    State srcState = whoFrom.getState();
    Info thisInfo = this->getInfo();
    State thisState = this->getState();
    Direction dirFrom;
    if(((thisInfo.row - 1) == srcInfo.row) && (thisInfo.col == srcInfo.col)){
        dirFrom = Direction::N;
    }
    else if(((thisInfo.row + 1) == srcInfo.row) && (thisInfo.col == srcInfo.col)){
        dirFrom = Direction::S;
    }
    else if((thisInfo.row  == srcInfo.row) && ((thisInfo.col + 1) == srcInfo.col)){
        dirFrom = Direction::W;
    }
    else if((thisInfo.row == srcInfo.row) && ((thisInfo.col - 1) == srcInfo.col)){
        dirFrom = Direction::E;
    }
    else if(((thisInfo.row + 1) == srcInfo.row) && ((thisInfo.col + 1) == srcInfo.col)){
        dirFrom = Direction::SE;
    }
    else if(((thisInfo.row + 1) == srcInfo.row) && ((thisInfo.col - 1) == srcInfo.col)){
        dirFrom = Direction::SW;
    }
    else if(((thisInfo.row - 1) == srcInfo.row) && ((thisInfo.col + 1) == srcInfo.col)){
        dirFrom = Direction::NE;
    }
    else{
        dirFrom = Direction::NW;
    }

    if (srcState.direction != dirFrom) { // wrong direction
        //cout << "fuck up 1" << endl;
        return;
    }
    /*if (thisState.type == StateType::NewPiece && thisInfo.colour == srcInfo.colour){ // when you hit the new piece on the way back
        State s;
        s.type = StateType::Relay;
        s.colour = thisInfo.colour;
        this->setState(s);
        cout << "fuck up 2" << endl;
        return;
    }*/
    if (thisState.type == StateType::NewPiece && srcState.type == StateType::Reply){
        return;
    }
    //if (thisState.type == StateType::Reply) return;
    if (thisInfo.colour == Colour::NoColour){ 
        //cout << "fuck up 3" << endl;
        return;
    }
    
    if (thisInfo.colour == srcInfo.colour && srcState.type == StateType::NewPiece) {
        //cout << "fuck up 4" << endl;
        return;
    }
    else if (thisInfo.colour != srcInfo.colour && srcState.type == StateType::NewPiece){
        State s{StateType::Relay, srcState.colour, dirFrom};
        this->setState(s);
        //cout << "case 1" << endl;
        this->notifyObservers();
    }
    else if (thisInfo.colour != srcInfo.colour && srcState.type == StateType::Relay){
        State s{StateType::Reply, srcState.colour, oppositeDir(dirFrom)};
        this->setState(s);
        //cout << "case 2" << endl;
        notifyObservers();
    }
    else if (thisInfo.colour == srcInfo.colour && srcState.type == StateType::Relay){
        State s{StateType::Relay, srcState.colour, dirFrom};
        this->setState(s);
        //cout << "case 3" << endl;
        notifyObservers();
    }
    else if (srcState.type == StateType::Reply && thisState.type == StateType::Relay){
        State s{StateType::Reply, srcState.colour, dirFrom};
        this->setState(s);
        this->toggle();
        //cout << "this shit just toggled" << endl;
        this->notifyObservers();
    }
    /*if(srcState.type != StateType::Reply){
        if (thisInfo.colour == srcInfo.colour && srcState.type == StateType::NewPiece) return;
        else if (thisInfo.colour != srcInfo.colour){
            thisState.type = StateType::Reply;
            dirFrom = oppositeDir(dirFrom);
            thisState.direction = dirFrom;
            notifyObservers();
        }
        else if(thisState.type != StateType::NewPiece){
            setState(StateType::Relay)
            //thisState.type = StateType::Relay;
            notifyObservers();
        }
        else{
            thisState.type = StateType::Reply;
            toggle();
            notifyObservers();
        }
    }*/
    

}

Info Cell::getInfo() const{
    Info i {r,c,colour};
    return i;
}
