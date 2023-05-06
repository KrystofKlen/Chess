#include "Game.h"
#include <iostream>

void Game::kickout(std::shared_ptr<Piece> pieceToKickout){
    int side = pieceToKickout->mSide;
    if(side == 1){
        piecesOUTplayer1.push_back(pieceToKickout);
    }else{
        piecesOUTplayer2.push_back(pieceToKickout);
    }
}

void Game::kickout(Coordinates coordinatesOfPieceToKickOut, std::list<std::shared_ptr<Piece>> & dstToMoveKickedPiece){
    Position & posRef = Board::playField[coordinatesOfPieceToKickOut.mRowIndex][coordinatesOfPieceToKickOut.mColumnIndex];
    int side = posRef.mPiece->mSide;
    if(side == 1){
        dstToMoveKickedPiece.push_back(posRef.mPiece);
        piecesINplayer1.remove(posRef.mPiece);
    }else{
        dstToMoveKickedPiece.push_back(posRef.mPiece);
        piecesINplayer2.remove(posRef.mPiece);
    }
    posRef.mIsFree = true;
    posRef.mPiece = nullptr;
 }

void Game::checkEnPassant(Coordinates selectedPosition, Coordinates pieceCoordinates){
    Position& positionWithPiece = Board::playField[pieceCoordinates.mRowIndex][pieceCoordinates.mColumnIndex];
    Position& selectedPosRef = Board::playField[selectedPosition.mRowIndex][selectedPosition.mColumnIndex];
    
    if(positionWithPiece.mPiece->mLetter != PAWN) return;
    if(!selectedPosRef.mIsFree) return;

    const Position* potentialTarget;
    if(positionWithPiece.mPiece->mSide == 2){
        if(selectedPosition.mRowIndex != 2) return;
        potentialTarget = &Board::playField[selectedPosition.mRowIndex + 1][selectedPosition.mColumnIndex];
    }else{
        if(selectedPosition.mRowIndex != 5) return;
        potentialTarget = &Board::playField[selectedPosition.mRowIndex - 1][selectedPosition.mColumnIndex];
    }

    if(
        potentialTarget->mIsFree ||
        potentialTarget->mPiece->mLetter != PAWN ||
        potentialTarget->mPiece->mSide == positionWithPiece.mPiece->mSide ||
        potentialTarget->mPiece->mNumOfStepsDone != 1
        ) return;
    
    kickout(potentialTarget->mPiece->mCoordinates, positionWithPiece.mPiece->mSide == 2 ? piecesOUTplayer1 : piecesOUTplayer2);
    
}

bool Game::detectCastlingAttempt( Coordinates selectedPosition , Coordinates piecePosition){
    char letter = Board::playField[piecePosition.mRowIndex][piecePosition.mColumnIndex].mPiece.get()->mLetter;
    if( letter != KING) return false;

    int kingColummIndex = Board::playField[piecePosition.mRowIndex][piecePosition.mColumnIndex].mPiece.get()->mCoordinates.mColumnIndex;
    if( abs(kingColummIndex - selectedPosition.mColumnIndex) > 1) return true;
    return false;
}

bool Game::moveIsValid(Coordinates coordinatesOfPieceToMove, Coordinates selectedPosition){
    std::list<Coordinates> possiblePositions;
    if(coordinatesOfPieceToMove == selectedPosition) return false;

    const Position & posRef = Board::playField[coordinatesOfPieceToMove.mRowIndex][coordinatesOfPieceToMove.mColumnIndex];

    posRef.mPiece->getPossibleMovePositions(possiblePositions);
    
    for(auto & possiblePosition : possiblePositions){
        if(possiblePosition == selectedPosition){   
            return true;
        }  
    }
    return false;
}

bool Game::checkIfPieceWasKickedOut(Coordinates coordinates){
    // if position a player wants go to is not free, it means that there is another piece
    // this piece must be a piece of other player, because moves to a position where a player already has it's piece are forbidden
    if(Board::playField[coordinates.mRowIndex][coordinates.mColumnIndex].mIsFree) return false;
    else return true;
}

bool Game::positionReachable(int playingSide, Coordinates positionToReach){

    std::list<Coordinates> possibleMoves;
    if(playingSide == 2){
    
        for(auto & piece : Game::piecesINplayer2){
            piece->getPossibleMovePositions(possibleMoves);
        }
    }else{
        for(auto & piece : piecesINplayer1){
            piece->getPossibleMovePositions(possibleMoves); 
        }
    }
    for(auto & move : possibleMoves){
        if(move == positionToReach){
            return true;
        }
    }
    return false;
}

bool Game::castle(Board & b, Coordinates selectedPosition, Coordinates pieceCoordinates){
    Position& positionWithPiece = Board::playField[pieceCoordinates.mRowIndex][pieceCoordinates.mColumnIndex];

    if( positionWithPiece.mIsFree || positionWithPiece.mPiece->mLetter != KING) return false;
    
    //side 1 SHORTER
    if(positionWithPiece.mPiece->mSide == 1 && pieceCoordinates.mColumnIndex < selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithPiece.mPiece.get()->mCoordinates.mColumnIndex; columnIndex <= selectedPosition.mColumnIndex; columnIndex++){
            if(positionReachable(2, {0,columnIndex})) {
                return false;
            }
        }

        addMoveToHistory({pieceCoordinates,selectedPosition},
        positionWithPiece.mPiece);
        addMoveToHistory({{0,7},{0,5}},
        Board::playField[0][7].mPiece);

        b.movePiece(pieceCoordinates, selectedPosition,true);
        b.movePiece({0,7},{0,5},true);
        return true;;
    }

    //side 1 LONGER
    if(positionWithPiece.mPiece->mSide == 1 && pieceCoordinates.mColumnIndex > selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithPiece.mPiece.get()->mCoordinates.mColumnIndex; columnIndex >= selectedPosition.mColumnIndex; columnIndex--){
            if(positionReachable(2, {0,columnIndex})){
                
                return false;
            } 
        }

        addMoveToHistory({pieceCoordinates,selectedPosition},
        positionWithPiece.mPiece);
        addMoveToHistory({{0,0},{0,3}},
        Board::playField[0][0].mPiece);

        b.movePiece(pieceCoordinates, selectedPosition,true);
        b.movePiece({0,0},{0,3}, true);
        return true;
    }

    //side 2 SHORTER
    if(positionWithPiece.mPiece->mSide == 2 && pieceCoordinates.mColumnIndex < selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithPiece.mPiece.get()->mCoordinates.mColumnIndex; columnIndex <= selectedPosition.mColumnIndex; columnIndex++){
            if(positionReachable(1, {7,columnIndex})){
                return false;
            } 
        }

        addMoveToHistory({pieceCoordinates,selectedPosition},
        positionWithPiece.mPiece);
        addMoveToHistory({{7,7},{7,5}},
        Board::playField[7][7].mPiece);

        b.movePiece(pieceCoordinates, selectedPosition,true);
        b.movePiece({7,7},{7,5},true);
        return true;
    }

    //side 2 LONGER
    if(positionWithPiece.mPiece->mSide == 2 && pieceCoordinates.mColumnIndex > selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithPiece.mPiece.get()->mCoordinates.mColumnIndex; columnIndex >= selectedPosition.mColumnIndex; columnIndex--){
            bool r = positionReachable(1, {7,columnIndex});
            if(r){
                return false;
            } 
        }

        addMoveToHistory({pieceCoordinates,selectedPosition},
        positionWithPiece.mPiece);
        addMoveToHistory({{7,0},{7,3}},
        Board::playField[7][0].mPiece);

        b.movePiece(pieceCoordinates, selectedPosition,true);
        b.movePiece({7,0},{7,3},true);
        return true;
    }
    return false;
}

bool Game::checkIfPawnReachedEnd(int playingSide){
    if(playingSide == 1){
        for(int columnIndex = 0; columnIndex<Board::BOARD_SIZE; columnIndex++){
            if( !Board::playField[7][columnIndex].mIsFree && Board::playField[7][columnIndex].mPiece->mLetter == 'P'){
                return true;
            }
        }
        return false;
    }
    else{
        for(int columnIndex = 0; columnIndex<Board::BOARD_SIZE; columnIndex++){
            if( !Board::playField[0][columnIndex].mIsFree && Board::playField[0][columnIndex].mPiece->mLetter == 'P'){
                return true;
            }
        }
        return false;
    }
}

void Game::addMoveToHistory(std::pair<Coordinates, Coordinates> fromTo, std::shared_ptr<Piece> ptrPiece){
    if(movesHistory.size() >= LIMIT_HIST_MOVES){
        movesHistory.pop_back();
    }
    movesHistory.push_front({fromTo.first,fromTo.second,ptrPiece});
}

const std::list<Game::MoveHistory> & Game::getMovesHistory() const{
    return movesHistory;
}

void Game::addMoveToHistory(const MoveHistory & move){
    movesHistory.push_back(move);
}

Game::Game(){

    //DEFAULT SETUP
    int idSerial = 0;
    //pieces side 1 default
    Coordinates c = {0,0};
    piecesPlayer1.push_back(std::make_shared <Rock> (1, c ,0, idSerial++) );  

    c = {0,1};
    piecesPlayer1.push_back(std::make_shared <Knight> (1, c ,0, idSerial++) ); 

    c = {0,2};
    piecesPlayer1.push_back(std::make_shared <Bishop> (1, c ,0, idSerial++) ); 

    c = {0,3};
    piecesPlayer1.push_back(std::make_shared <Queen> (1, c ,0, idSerial++) ); 

    c = {0,4};
    piecesPlayer1.push_back(std::make_shared <King> (1, c ,0, idSerial++) );

    c = {0,5};
    piecesPlayer1.push_back(std::make_shared <Bishop> (1, c ,0, idSerial++) );

    c = {0,6};
    piecesPlayer1.push_back(std::make_shared <Knight> (1, c ,0, idSerial++) ); 

    c = {0,7};
    piecesPlayer1.push_back(std::make_shared <Rock> (1, c ,0, idSerial++) ); 

    for(int columIndex = 0; columIndex < Board::BOARD_SIZE; columIndex++){
        c = {1, columIndex};
        piecesPlayer1.push_back(std::make_shared <Pawn> (1, c ,0, idSerial++) );
    }
    
    //pieces side 2 default
    c = {7,0};
    piecesPlayer2.push_back(std::make_shared <Rock> (2, c ,0, idSerial++) );  

    c = {7,1};
    piecesPlayer2.push_back(std::make_shared <Knight> (2, c ,0, idSerial++) ); 

    c = {7,2};
    piecesPlayer2.push_back(std::make_shared <Bishop> (2, c ,0, idSerial++) ); 

    c = {7,3};
    piecesPlayer2.push_back(std::make_shared <Queen> (2, c ,0, idSerial++) ); 

    c = {7,4};
    piecesPlayer2.push_back(std::make_shared <King> (2, c ,0, idSerial++) );

    c = {7,5};
    piecesPlayer2.push_back(std::make_shared <Bishop> (2, c ,0, idSerial++) );

    c = {7,6};
    piecesPlayer2.push_back(std::make_shared <Knight> (2, c ,0, idSerial++) ); 

    c = {7,7};
    piecesPlayer2.push_back(std::make_shared <Rock> (2, c ,0, idSerial++) ); 

    for(int columIndex = 0; columIndex < Board::BOARD_SIZE; columIndex++){
        c = {6, columIndex};
        piecesPlayer2.push_back(std::make_shared <Pawn> (2, c ,0, idSerial++) );
    }

    //set pieces IN, in the default setup there are no pieces OUT
    for(auto & x : piecesPlayer1){
        piecesINplayer1.push_back(x);
    }
    for(auto & x : piecesPlayer2){
        piecesINplayer2.push_back(x);
    }     
}

void Game::clearDefault(){
    piecesPlayer1.clear();
    piecesPlayer2.clear();
    piecesINplayer1.clear();
    piecesINplayer2.clear();
    piecesOUTplayer1.clear();
    piecesOUTplayer2.clear();
}

void Game::findKingsIndex(){
    int index = 0;
    for(auto & x : piecesPlayer1){
        if(x->mLetter == KING){
            indexOfKingSide1 = index;
            std::cout<<indexOfKingSide1<<std::endl;
        }
            
        else 
            index++;
    }
    index = 0;
    for(auto & x : piecesPlayer2){
        if(x->mLetter == KING){
            indexOfKingSide2 = index;
            std::cout<<indexOfKingSide1<<std::endl;
        }
            
        else 
            index++;
    }
}
