#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

// Recommended rank = 100

class Bishop : public  Piece{
public:
    Bishop(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Bishop(const Bishop & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};