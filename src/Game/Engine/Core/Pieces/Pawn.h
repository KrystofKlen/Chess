#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

// Recommended rank = 30

class Pawn : public  Piece{
public:
    Pawn(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Pawn(const Pawn & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};