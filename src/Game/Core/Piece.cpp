#include <list>
#include "Piece.h"

Figure::Figure(int maxNumberOfSteps, char letter, int side, 
Coordinates innitCoordinates, int numOfStepsDone, int id, int rank){
    mMaxNumberOfSteps = maxNumberOfSteps;
    mLetter = letter;
    mSide = side;
    mCoordinates = innitCoordinates;
    mNumOfStepsDone = numOfStepsDone;
    mId = id;
    mRank = rank;
}

Figure::Figure(const Figure & figure){
    mMaxNumberOfSteps = figure.mMaxNumberOfSteps;
    mLetter = figure.mLetter;
    mSide = figure.mSide;
    mCoordinates.setCoordinates( figure.mCoordinates );
    mNumOfStepsDone = figure.mNumOfStepsDone;
}