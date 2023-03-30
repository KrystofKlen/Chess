#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

const int queenRank = 250;

class Queen :  public  Piece{
public:
    Queen(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Queen(const Queen & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};