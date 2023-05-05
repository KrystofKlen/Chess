#include "Converter.h"


void Converter::readNextChunk(std::stringstream & strStream, char delimiter, const std::string & fileContent, std::string::const_iterator & it){
    strStream.str("");
    while(*it != delimiter){
        strStream<<*it;
        it++;
    }
    it++;
    it++;
}

void Converter::breakUpChunks(const std::string & strChunk, std::list<std::string> & chunks){
    std::stringstream strStream;
    std::string::const_iterator it = strChunk.begin();
    while(it != strChunk.end()){
        while(*it != '\n'){
            strStream<<*it;
            it++;
        }
        chunks.push_back(strStream.str());
        strStream.str("");
        it++;
    }
}

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


std::shared_ptr<Piece> Converter::createPieceFromChunk(const std::string & pieceData){

    int ASCII_CONSTANT = 48;

    std::string::const_iterator it = pieceData.begin();
    char letter = *it;
    it++;
    it++;
    int side = *it - ASCII_CONSTANT;
    it++;
    it++;
    it++;
    int rowIndex = *it - ASCII_CONSTANT;
    it++;
    it++;
    int columnIndexIndex = *it - ASCII_CONSTANT;
    it++;
    it++;
    it++;
    std::string buffer;
    while(*it != ','){
        buffer.push_back(*it);
        it++;
    }

    int numOfStepsDone;
    try{
        numOfStepsDone = std::stoi(buffer);
    }catch(...) {
        return nullptr;
    }
    it++;
    buffer.clear();
    while(*it != '}'){
        buffer.push_back(*it);
        it++;
    }

    int id;
    try{
        id = std::stoi(buffer);
    }catch(...){
        return nullptr;
    }
    
    Coordinates c;

    switch (letter)
    {
    case 'K':
        c = {rowIndex,columnIndexIndex};
        return std::make_shared<King> (side,c,numOfStepsDone,id);
        break;
    case 'Q':
        c = {rowIndex,columnIndexIndex};
        return std::make_shared<Queen> (side,c,numOfStepsDone,id);
        break;
    case 'B':
        c = {rowIndex,columnIndexIndex};
        return std::make_shared<Bishop> (side,c,numOfStepsDone,id);
        break;
    case 'H':
        c = {rowIndex,columnIndexIndex};
        return std::make_shared<Knight> (side,c,numOfStepsDone,id);
        break;
    case 'R':
        c = {rowIndex,columnIndexIndex};
        return std::make_shared<Rock> (side,c,numOfStepsDone,id);
        break;
    case 'P':
        c = {rowIndex,columnIndexIndex};
        return std::make_shared<Pawn> (side,c,numOfStepsDone,id);
        break;
    
    default:
        return nullptr;
    }
    return nullptr;
}


std::shared_ptr<Piece> Converter::createPieceFromFileData(const PieceFileData & pieceFileData){
    Coordinates c = {pieceFileData.mRowIndex, pieceFileData.mColumnIndex};

    switch (pieceFileData.mLetter)
    {
    case 'K':
        return std::make_shared<King> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case 'Q':
        return std::make_shared<Queen> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case 'B':
        return std::make_shared<Bishop> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case 'H':
        return std::make_shared<Knight> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case 'R':
        return std::make_shared<Rock> (pieceFileData.mSide,c,pieceFileData.mNumOfStepsDone,pieceFileData.mId);
        break;
    case 'P':
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