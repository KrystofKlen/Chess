#include <list>
#include "Piece.h"

Piece::Piece(int maxNumberOfSteps, char letter, int side, 
Coordinates innitCoordinates, int numOfStepsDone, int id, int rank){
    mMaxNumberOfSteps = maxNumberOfSteps;
    mLetter = letter;
    mSide = side;
    mCoordinates = innitCoordinates;
    mNumOfStepsDone = numOfStepsDone;
    mId = id;
    mRank = rank;
}

Piece::Piece(const Piece & piece){
    mMaxNumberOfSteps = piece.mMaxNumberOfSteps;
    mLetter = piece.mLetter;
    mSide = piece.mSide;
    mCoordinates.setCoordinates( piece.mCoordinates );
    mNumOfStepsDone = piece.mNumOfStepsDone;
}