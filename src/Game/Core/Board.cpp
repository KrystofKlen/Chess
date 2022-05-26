#include "Board.h"

Position Board::playField[BOARD_SIZE][BOARD_SIZE];

void Board::refreshFigureCoordinates(){
    for (int rowIndex = 0; rowIndex < 8; rowIndex++){
        for (int columnIndex = 0; columnIndex < 8; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree ){
                posRef.mFigure->mCoordinates = {rowIndex, columnIndex};
            }
        }     
    }
}



void Board::moveFigure(Coordinates from, Coordinates to, bool shouldIncreaseNumberOfSteps){
    if( playField[from.mRowIndex][from.mColumnIndex].mIsFree) return;
    if( from == to) return;

    playField[to.mRowIndex][to.mColumnIndex].mFigure = 
    playField[from.mRowIndex][from.mColumnIndex].mFigure;

    playField[from.mRowIndex][from.mColumnIndex].mFigure = nullptr;
    playField[to.mRowIndex][to.mColumnIndex].mIsFree = false;
    playField[from.mRowIndex][from.mColumnIndex].mIsFree = true;

    playField[to.mRowIndex][to.mColumnIndex].mFigure->mCoordinates.mRowIndex = to.mRowIndex;
    playField[to.mRowIndex][to.mColumnIndex].mFigure->mCoordinates.mColumnIndex = to.mColumnIndex;

    if(shouldIncreaseNumberOfSteps)
        playField[to.mRowIndex][to.mColumnIndex].mFigure->mNumOfStepsDone++;
        
}


void Board::setFiguresOnBoard(const std::list<std::shared_ptr<Figure>> & figuresPlayer1, const std::list<std::shared_ptr<Figure>> & figuresPlayer2){
    for(auto x : figuresPlayer1){
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mIsFree = false;
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mFigure = x;
    }
    for(auto x : figuresPlayer2){
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mIsFree = false;
        Board::playField[x->mCoordinates.mRowIndex][x->mCoordinates.mColumnIndex].mFigure = x;
    }
}

Board::Board(){}



