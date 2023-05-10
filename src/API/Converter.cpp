#include "Converter.h"

void Converter::convertPiece(std::shared_ptr<Piece> from, PieceFileData & to){
    to.mLetter = from->mLetter;
    to.mSide = from->mSide;
    to.mRowIndex = from->mCoordinates.mRowIndex;
    to.mColumnIndex = from->mCoordinates.mColumnIndex;
    to.mNumOfStepsDone = from->mNumOfStepsDone;
    to.mId = from->mId;
}

void Converter::convertHistoryMove(const Game::MoveHistory & from, HistoryFileData & to){
    to.mLetter = from.ptrPiece.get()->mLetter;
    to.mSide = from.ptrPiece.get()->mSide;
    to.mCoordinateFromRowIndex = from.from.mRowIndex;
    to.mCoordinateFromColIndex = from.from.mColumnIndex;
    to.mCoordinateToRowIndex = from.to.mRowIndex;
    to.mCoordinateToColIndex = from.to.mColumnIndex;
}

void Converter::convertHistoryMoveFileData(const HistoryFileData & from, Game::MoveHistory & to){
    int DOESNT_MATTER = 0;
    to.ptrPiece = createPieceFromFileData(
        {from.mLetter,from.mSide,DOESNT_MATTER,DOESNT_MATTER,DOESNT_MATTER,DOESNT_MATTER}
        );
    to.from.mRowIndex = from.mCoordinateFromRowIndex;
    to.from.mColumnIndex = from.mCoordinateFromColIndex;
    to.to.mRowIndex = from.mCoordinateToRowIndex;
    to.to.mColumnIndex = from.mCoordinateToColIndex;
}

std::shared_ptr<Piece> Converter::createPieceFromFileData(const PieceFileData & pieceFileData){
    Coordinates c = {pieceFileData.mRowIndex, pieceFileData.mColumnIndex};

    switch (pieceFileData.mLetter)
    {
    case KING:
        return std::make_shared<King> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case QUEEN:
        return std::make_shared<Queen> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case BISHOP:
        return std::make_shared<Bishop> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case KNIGHT:
        return std::make_shared<Knight> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case ROCK:
        return std::make_shared<Rock> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case PAWN:
        return std::make_shared<Pawn> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    
    default:
        return nullptr;
    }
    return nullptr;
}


void Converter::setIsFreeData(const std::string & strIsFree){
    int strIsFreeIndex = 0;
    for(int rowIndex = 0; rowIndex < 8; rowIndex++,strIsFreeIndex++){
        for(int columnIndex = 0; columnIndex<8; columnIndex++, strIsFreeIndex++){
            if(strIsFree[strIsFreeIndex] == '1'){
                Board::playField[rowIndex][columnIndex].mIsFree = true;
            }else{
                Board::playField[rowIndex][columnIndex].mIsFree = false;
            }
        }
    }
}

void Converter::setIsFreeData(const int board[8][8]){
    for(int rowIndex = 0; rowIndex < 8; rowIndex++){
        for(int columnIndex = 0; columnIndex<8; columnIndex++){
            if(board[rowIndex][columnIndex] == 1)
                Board::playField[rowIndex][columnIndex].mIsFree = true;
            else
                Board::playField[rowIndex][columnIndex].mIsFree = false;
        }
    }
}

void Converter::getIsFreeData(int board[8][8]){
    for(int rowIndex = 0; rowIndex < 8; rowIndex++){
        for(int columnIndex = 0; columnIndex<8; columnIndex++){
            if(Board::playField[rowIndex][columnIndex].mIsFree)
                board[rowIndex][columnIndex]=1;
            else
                board[rowIndex][columnIndex]=0;  
        }
    }
}