#include "King.h"

//---------- KING -----------------------------------------------------------------
King::King(int side, Coordinates initCoordinates, int numOfStepsDone, int id)
 : Figure(1,'K',side,initCoordinates,numOfStepsDone, id, kingRank){
    mCastlePossible = true;
}
King::King(const King & ref)
 : Figure(ref.mSide, ref.mLetter,ref.mSide, ref.mCoordinates, ref.mNumOfStepsDone, ref.mId, kingRank ){

}

void King::modifyRank(){
    //To be implemented
}

void King::getPossibleMovePositions(std::list<Coordinates> & possiblePositions){
    addMovesVertical(possiblePositions,*this);
    addMovesHorizontal(possiblePositions,*this);
    addMoves1Quadrant(possiblePositions,*this);
    addMoves2Quadrant(possiblePositions,*this);
    addMoves3Quadrant(possiblePositions,*this);
    addMoves4Quadrant(possiblePositions,*this);
    addCastlingPositionsForKing(possiblePositions,*this);
    //clearCheckMoves(possiblePositions,*this);
}