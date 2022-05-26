#include "Queen.h"

//---------- QUEEN -----------------------------------------------------------------
Queen::Queen(int side, Coordinates initCoordinates, int numOfStepsDone, int id)
 : Figure(8,'Q',side,initCoordinates,numOfStepsDone, id, queenRank){

}
Queen::Queen(const Queen & ref)
 : Figure(ref.mMaxNumberOfSteps, ref.mLetter, ref.mSide, ref.mCoordinates, ref.mNumOfStepsDone, ref.mId,queenRank ){

}
void Queen::modifyRank(){
    //To be implemented
}
void Queen::getPossibleMovePositions(std::list<Coordinates> & possiblePositions){
    addMovesVertical(possiblePositions,*this);
    addMovesHorizontal(possiblePositions,*this);
    addMoves1Quadrant(possiblePositions,*this);
    addMoves2Quadrant(possiblePositions,*this);
    addMoves3Quadrant(possiblePositions,*this);
    addMoves4Quadrant(possiblePositions,*this);
}