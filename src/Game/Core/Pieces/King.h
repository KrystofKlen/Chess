#pragma once
#include "../Piece.h" 
#include "../Moves.h"
#include "../Coordinates.h"

const int kingRank = 10000;

class King : public Piece{
public:
    King(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    King(const King & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
private:
    bool mCastlePossible;
};