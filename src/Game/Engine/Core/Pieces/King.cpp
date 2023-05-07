#include "King.h"

//---------- KING -----------------------------------------------------------------
King::King(int side, Coordinates initCoordinates, int numOfStepsDone, int id)
 : Piece(1,'K',side,initCoordinates,numOfStepsDone, id, KING_RANK){
    mCastlePossible = true;
}
King::King(const King & ref)
 : Piece(ref.mSide, ref.mLetter,ref.mSide, ref.mCoordinates, ref.mNumOfStepsDone, ref.mId, KING_RANK ){

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