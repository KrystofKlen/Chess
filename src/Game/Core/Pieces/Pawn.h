#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

const int pawnRank = 30;

class Pawn : public  Figure{
public:
    Pawn(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Pawn(const Pawn & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};