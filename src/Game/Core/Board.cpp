#include "Board.h"

Position Board::playField[BOARD_SIZE][BOARD_SIZE];

void Board::refreshPieceCoordinates(){
    for (int rowIndex = 0; rowIndex < Board::BOARD_SIZE; rowIndex++){
        for (int columnIndex = 0; columnIndex < Board::BOARD_SIZE; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree ){
                posRef.mPiece->mCoordinates = {rowIndex, columnIndex};
            }
        }     
    }
}



void Board::movePiece(Coordinates from, Coordinates to, bool shouldIncreaseNumberOfSteps){
    if( playField[from.mRowIndex][from.mColumnIndex].mIsFree) return;
    if( from == to) return;

    playField[to.mRowIndex][to.mColumnIndex].mPiece = 
    playField[from.mRowIndex][from.mColumnIndex].mPiece;

    playField[from.mRowIndex][from.mColumnIndex].mPiece = nullptr;
    playField[to.mRowIndex][to.mColumnIndex].mIsFree = false;
    playField[from.mRowIndex][from.mColumnIndex].mIsFree = true;

    playField[to.mRowIndex][to.mColumnIndex].mPiece->mCoordinates.mRowIndex = to.mRowIndex;
    playField[to.mRowIndex][to.mColumnIndex].mPiece->mCoordinates.mColumnIndex = to.mColumnIndex;

    if(shouldIncreaseNumberOfSteps)
        playField[to.mRowIndex][to.mColumnIndex].mPiece->mNumOfStepsDone++;
        
}


void Board::setPiecesOnBoard(const std::list<std::shared_ptr<Piece>> & piecesPlayer1, const std::list<std::shared_ptr<Piece>> & piecesPlayer2){
    for(auto x : piecesPlayer1){
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mIsFree = false;
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mPiece = x;
    }
    for(auto x : piecesPlayer2){
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mIsFree = false;
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mPiece = x;
    }
}

Board::Board(){}



