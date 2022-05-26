#pragma once
#include "Coordinates.h"
#include <list>

class Figure{

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
     *  which Figure(King, Queen .. or other Figure inheriting from this class) can go to
     */
    virtual void getPossibleMovePositions(std::list<Coordinates> & possiblePositions) = 0;

    /**
     * This function will modify figures rank, it is up to you how you'll implement this.
     * Default implementation is empty.
     */
    virtual void modifyRank() = 0;
    
    Figure(int maxNumberOfSteps, char letter, int side, 
    Coordinates initCoordinates, int numOfStepsDone, int id, int rank);
    Figure(const Figure & Figure);
    virtual ~Figure(){}
private:
    

};

