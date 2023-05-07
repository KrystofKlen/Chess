#include "Pawn.h"

//---------- PAWN -----------------------------------------------------------------
Pawn::Pawn(int side, Coordinates initCoordinates,int numOfStepsDone, int id)
 : Piece(1,'P',side,initCoordinates,numOfStepsDone, id, PAWN_RANK){
}
Pawn::Pawn(const Pawn & ref)
 : Piece(ref.mMaxNumberOfSteps, ref.mLetter, ref.mSide, ref.mCoordinates, ref.mNumOfStepsDone, ref.mId , PAWN_RANK){

}

void Pawn::modifyRank(){
    //To be implemented
}
void Pawn::getPossibleMovePositions(std::list<Coordinates> & possiblePositions){
    
    if(this->mSide == 2){
        if(this->mCoordinates.mRowIndex - 1 >= 0){
            if(Board::playField[this->mCoordinates.mRowIndex - 1][this->mCoordinates.mColumnIndex].mIsFree)
                possiblePositions.push_back({ this->mCoordinates.mRowIndex - 1, this->mCoordinates.mColumnIndex});

            addQuadrantsForPawnSide2(possiblePositions, *this);
        }

        if(mNumOfStepsDone == 0 && Board::playField[this->mCoordinates.mRowIndex - 2][this->mCoordinates.mColumnIndex].mIsFree){
            possiblePositions.push_back({this->mCoordinates.mRowIndex - 2, this->mCoordinates.mColumnIndex });
        }

    }else{
        if(this->mCoordinates.mRowIndex + 1 < 8){
            if(Board::playField[this->mCoordinates.mRowIndex + 1][this->mCoordinates.mColumnIndex].mIsFree)
                possiblePositions.push_back({this->mCoordinates.mRowIndex + 1, this->mCoordinates.mColumnIndex});

            addQuadrantsForPawnSide1(possiblePositions, *this);
        }

        if(mNumOfStepsDone == 0 && Board::playField[this->mCoordinates.mRowIndex + 2][this->mCoordinates.mColumnIndex].mIsFree){
            possiblePositions.push_back({ this->mCoordinates.mRowIndex + 2, this->mCoordinates.mColumnIndex});
        }
    }
    addEnPassantForPawn(possiblePositions, *this);
}
