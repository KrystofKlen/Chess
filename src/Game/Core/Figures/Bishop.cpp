#include "Bishop.h"
//---------- BISHOP -----------------------------------------------------------------
Bishop::Bishop(int side, Coordinates initCoordinates, int numOfStepsDone, int id)
 : Figure(8,'B',side,initCoordinates,numOfStepsDone, id, bishopRank){

}
Bishop::Bishop(const Bishop & ref)
 : Figure( ref.mMaxNumberOfSteps , ref.mLetter, ref.mSide, ref.mCoordinates, ref.mNumOfStepsDone, ref.mId, bishopRank){

}

void Bishop::modifyRank(){
    //To be implemented
}

void Bishop::getPossibleMovePositions(std::list<Coordinates> & possiblePositions){
    addMoves1Quadrant(possiblePositions,*this);
    addMoves2Quadrant(possiblePositions,*this);
    addMoves3Quadrant(possiblePositions,*this);
    addMoves4Quadrant(possiblePositions,*this);
}