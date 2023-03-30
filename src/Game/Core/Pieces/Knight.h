#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

const int knightRank = 100;

class Knight : public  Piece{
public:
    Knight(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Knight(const Knight& ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};