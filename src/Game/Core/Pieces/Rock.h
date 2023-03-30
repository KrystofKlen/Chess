#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

const int rockRank = 100;

class Rock : public  Piece{
public:
    Rock(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Rock(const Rock & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};