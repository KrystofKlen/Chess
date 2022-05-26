#pragma once
#include "../Figure.h" 
#include "../Moves.h"
#include "../Coordinates.h"

const int bishopRank = 100;

class Bishop : public  Figure{
public:
    Bishop(int side, Coordinates initCoordinates, int numOfStepsDone, int id);
    Bishop(const Bishop & ref);
    void getPossibleMovePositions(std::list<Coordinates> & possiblePositions);
    void modifyRank();
};