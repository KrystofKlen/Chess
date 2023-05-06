#pragma once
#include "Coordinates.h"
#include <list>

class Piece{

public:
    char mLetter;
    int mSide;
    Coordinates mCoordinates;
    int mMaxNumberOfSteps;
    int mNumOfStepsDone;
    int mId;
    int mRank;
    bool isInSimulation = true;
    /**
     * This function will fill possiblePositions with coordinates of positions,
     *  which Piece(King, Queen .. or other Piece inheriting from this class) can go to
     */
    virtual void getPossibleMovePositions(std::list<Coordinates> & possiblePositions) = 0;

    /**
     * This function will modify Pieces rank, it is up to you how you'll implement this.
     * Default implementation is empty.
     */
    virtual void modifyRank() = 0;
    
    Piece(int maxNumberOfSteps, char letter, int side, 
    Coordinates initCoordinates, int numOfStepsDone, int id, int rank);
    Piece(const Piece & Piece);
    virtual ~Piece(){}
private:
    

};

