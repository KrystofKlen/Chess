#include "Knight.h"
//---------- KNIGHT -----------------------------------------------------------------
Knight::Knight(int side, Coordinates initCoordinates, int numOfStepsDone, int id)
 : Piece(3,'H',side,initCoordinates,numOfStepsDone, id, knightRank){

}
Knight::Knight(const Knight & ref)
 : Piece(ref.mMaxNumberOfSteps, ref.mLetter, ref.mSide, ref.mCoordinates, ref.mNumOfStepsDone, ref.mId, knightRank ){

}
void Knight::modifyRank(){
    //To be implemented
}
void Knight::getPossibleMovePositions(std::list<Coordinates> & possiblePositions){
    addMovesKnight(possiblePositions, *this);
}