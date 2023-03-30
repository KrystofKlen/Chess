#include "Position.h"

Position::Position(const Position & pos){
    mRowIndex = pos.mRowIndex;
    mColumnIndex = pos.mColumnIndex;
    mIsFree = pos.mIsFree;
    ptrToPositionOnWhichIsPawnThatCanBeKickedUsingEnPassant = pos.ptrToPositionOnWhichIsPawnThatCanBeKickedUsingEnPassant;
    mPiece = pos.mPiece;
}

Position::Position(){}