#include "Game.h"
#include <iostream>

void Game::kickout(std::shared_ptr<Figure> figureToKickout){
    int side = figureToKickout->mSide;
    if(side == 1){
        figuresOUTplayer1.push_back(figureToKickout);
    }else{
        figuresOUTplayer2.push_back(figureToKickout);
    }
}

void Game::kickout(Coordinates coordinatesOfFigureToKickOut, std::list<std::shared_ptr<Figure>> & dstToMoveKickedFigure){
    Position & posRef = Board::playField[coordinatesOfFigureToKickOut.mRowIndex][coordinatesOfFigureToKickOut.mColumnIndex];
    int side = posRef.mFigure->mSide;
    if(side == 1){
        dstToMoveKickedFigure.push_back(posRef.mFigure);
        figuresINplayer1.remove(posRef.mFigure);
    }else{
        dstToMoveKickedFigure.push_back(posRef.mFigure);
        figuresINplayer2.remove(posRef.mFigure);
    }
    posRef.mIsFree = true;
    posRef.mFigure = nullptr;
 }

void Game::checkEnPassant(Coordinates selectedPosition, Coordinates figureCoordinates){
    Position& positionWithFigure = Board::playField[figureCoordinates.mRowIndex][figureCoordinates.mColumnIndex];
    Position& selectedPosRef = Board::playField[selectedPosition.mRowIndex][selectedPosition.mColumnIndex];
    
    if(positionWithFigure.mFigure->mLetter != 'P') return;
    if(!selectedPosRef.mIsFree) return;

    const Position* potentialTarget;
    if(positionWithFigure.mFigure->mSide == 2){
        if(selectedPosition.mRowIndex != 2) return;
        potentialTarget = &Board::playField[selectedPosition.mRowIndex + 1][selectedPosition.mColumnIndex];
    }else{
        if(selectedPosition.mRowIndex != 5) return;
        potentialTarget = &Board::playField[selectedPosition.mRowIndex - 1][selectedPosition.mColumnIndex];
    }

    if(
        potentialTarget->mIsFree ||
        potentialTarget->mFigure->mLetter != 'P' ||
        potentialTarget->mFigure->mSide == positionWithFigure.mFigure->mSide ||
        potentialTarget->mFigure->mNumOfStepsDone != 1
        ) return;
    
    kickout(potentialTarget->mFigure->mCoordinates, positionWithFigure.mFigure->mSide == 2 ? figuresOUTplayer1 : figuresOUTplayer2);
    
}

bool Game::detectCastlingAttempt( Coordinates selectedPosition , Coordinates figurePosition){
    char letter = Board::playField[figurePosition.mRowIndex][figurePosition.mColumnIndex].mFigure.get()->mLetter;
    if( letter != 'K') return false;

    int kingColummIndex = Board::playField[figurePosition.mRowIndex][figurePosition.mColumnIndex].mFigure.get()->mCoordinates.mColumnIndex;
    if( abs(kingColummIndex - selectedPosition.mColumnIndex) > 1) return true;
    return false;
}

bool Game::moveIsValid(Coordinates coordinatesOfFigureToMove, Coordinates selectedPosition){
    std::list<Coordinates> possiblePositions;
    if(coordinatesOfFigureToMove == selectedPosition) return false;

    const Position & posRef = Board::playField[coordinatesOfFigureToMove.mRowIndex][coordinatesOfFigureToMove.mColumnIndex];

    posRef.mFigure->getPossibleMovePositions(possiblePositions);
    
    for(auto & possiblePosition : possiblePositions){
        if(possiblePosition == selectedPosition){   
            return true;
        }  
    }
    return false;
}

bool Game::checkIfFigureWasKickedOut(Coordinates coordinates){
    // if position a player wants go to is not free, it means that there is another figure
    // this figure must be a figure of other player, because moves to a position where a player already has it's figure are forbidden
    if(Board::playField[coordinates.mRowIndex][coordinates.mColumnIndex].mIsFree) return false;
    else return true;
}

bool Game::positionReachable(int playingSide, Coordinates positionToReach){

    std::list<Coordinates> possibleMoves;
    if(playingSide == 2){
    
        for(auto & figure : Game::figuresINplayer2){
            figure->getPossibleMovePositions(possibleMoves);
        }
    }else{
        for(auto & figure : figuresINplayer1){
            figure->getPossibleMovePositions(possibleMoves); 
        }
    }
    for(auto & move : possibleMoves){
        if(move == positionToReach){
            return true;
        }
    }
    return false;
}

bool Game::castle(Board & b, Coordinates selectedPosition, Coordinates figureCoordinates){
    Position& positionWithFigure = Board::playField[figureCoordinates.mRowIndex][figureCoordinates.mColumnIndex];

    if( positionWithFigure.mIsFree || positionWithFigure.mFigure->mLetter != 'K') return false;
    
    //side 1 SHORTER
    if(positionWithFigure.mFigure->mSide == 1 && figureCoordinates.mColumnIndex < selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithFigure.mFigure.get()->mCoordinates.mColumnIndex; columnIndex <= selectedPosition.mColumnIndex; columnIndex++){
            if(positionReachable(2, {0,columnIndex})) {
                return false;
            }
        }
        b.moveFigure(figureCoordinates, selectedPosition,true);
        b.moveFigure({0,7},{0,5},true);
        return true;;
    }

    //side 1 LONGER
    if(positionWithFigure.mFigure->mSide == 1 && figureCoordinates.mColumnIndex > selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithFigure.mFigure.get()->mCoordinates.mColumnIndex; columnIndex >= selectedPosition.mColumnIndex; columnIndex--){
            if(positionReachable(2, {0,columnIndex})){
                
                return false;
            } 
        }
        b.moveFigure(figureCoordinates, selectedPosition,true);
        b.moveFigure({0,0},{0,3}, true);
        return true;
    }

    //side 2 SHORTER
    if(positionWithFigure.mFigure->mSide == 2 && figureCoordinates.mColumnIndex < selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithFigure.mFigure.get()->mCoordinates.mColumnIndex; columnIndex <= selectedPosition.mColumnIndex; columnIndex++){
            if(positionReachable(1, {7,columnIndex})){
                return false;
            } 
        }
        b.moveFigure(figureCoordinates, selectedPosition,true);
        b.moveFigure({7,7},{7,5},true);
        return true;
    }

    //side 2 LONGER
    if(positionWithFigure.mFigure->mSide == 2 && figureCoordinates.mColumnIndex > selectedPosition.mColumnIndex ){
        for(int columnIndex = positionWithFigure.mFigure.get()->mCoordinates.mColumnIndex; columnIndex >= selectedPosition.mColumnIndex; columnIndex--){
            bool r = positionReachable(1, {7,columnIndex});
            if(r){
                return false;
            } 
        }
        b.moveFigure(figureCoordinates, selectedPosition,true);
        b.moveFigure({7,0},{7,3},true);
        return true;
    }
    return false;
}

bool Game::checkIfPawnReachedEnd(int playingSide){
    if(playingSide == 1){
        for(int columnIndex = 0; columnIndex<8; columnIndex++){
            if( !Board::playField[7][columnIndex].mIsFree && Board::playField[7][columnIndex].mFigure->mLetter == 'P'){
                return true;
            }
        }
        return false;
    }
    else{
        for(int columnIndex = 0; columnIndex<8; columnIndex++){
            if( !Board::playField[0][columnIndex].mIsFree && Board::playField[0][columnIndex].mFigure->mLetter == 'P'){
                return true;
            }
        }
        return false;
    }
}


Game::Game(){

    //DEFAULT SETUP
    int idSerial = 0;
    //figures side 1 default
    Coordinates c = {0,0};
    figuresPlayer1.push_back(std::make_shared <Rock> (1, c ,0, idSerial++) );  

    c = {0,1};
    figuresPlayer1.push_back(std::make_shared <Knight> (1, c ,0, idSerial++) ); 

    c = {0,2};
    figuresPlayer1.push_back(std::make_shared <Bishop> (1, c ,0, idSerial++) ); 

    c = {0,3};
    figuresPlayer1.push_back(std::make_shared <Queen> (1, c ,0, idSerial++) ); 

    c = {0,4};
    figuresPlayer1.push_back(std::make_shared <King> (1, c ,0, idSerial++) );

    c = {0,5};
    figuresPlayer1.push_back(std::make_shared <Bishop> (1, c ,0, idSerial++) );

    c = {0,6};
    figuresPlayer1.push_back(std::make_shared <Knight> (1, c ,0, idSerial++) ); 

    c = {0,7};
    figuresPlayer1.push_back(std::make_shared <Rock> (1, c ,0, idSerial++) ); 

    for(int columIndex = 0; columIndex < Board::BOARD_SIZE; columIndex++){
        c = {1, columIndex};
        figuresPlayer1.push_back(std::make_shared <Pawn> (1, c ,0, idSerial++) );
    }
    
    //figures side 2 default
    c = {7,0};
    figuresPlayer2.push_back(std::make_shared <Rock> (2, c ,0, idSerial++) );  

    c = {7,1};
    figuresPlayer2.push_back(std::make_shared <Knight> (2, c ,0, idSerial++) ); 

    c = {7,2};
    figuresPlayer2.push_back(std::make_shared <Bishop> (2, c ,0, idSerial++) ); 

    c = {7,3};
    figuresPlayer2.push_back(std::make_shared <Queen> (2, c ,0, idSerial++) ); 

    c = {7,4};
    figuresPlayer2.push_back(std::make_shared <King> (2, c ,0, idSerial++) );

    c = {7,5};
    figuresPlayer2.push_back(std::make_shared <Bishop> (2, c ,0, idSerial++) );

    c = {7,6};
    figuresPlayer2.push_back(std::make_shared <Knight> (2, c ,0, idSerial++) ); 

    c = {7,7};
    figuresPlayer2.push_back(std::make_shared <Rock> (2, c ,0, idSerial++) ); 

    for(int columIndex = 0; columIndex < Board::BOARD_SIZE; columIndex++){
        c = {6, columIndex};
        figuresPlayer2.push_back(std::make_shared <Pawn> (2, c ,0, idSerial++) );
    }

    //set figures IN, in the default setup there are no figures OUT
    for(auto & x : figuresPlayer1){
        figuresINplayer1.push_back(x);
    }
    for(auto & x : figuresPlayer2){
        figuresINplayer2.push_back(x);
    }     
}

void Game::clearDefault(){
    figuresPlayer1.clear();
    figuresPlayer2.clear();
    figuresINplayer1.clear();
    figuresINplayer2.clear();
    figuresOUTplayer1.clear();
    figuresOUTplayer2.clear();
}

void Game::findKingsIndex(){
    int index = 0;
    for(auto & x : figuresPlayer1){
        if(x->mLetter == 'K'){
            indexOfKingSide1 = index;
            std::cout<<indexOfKingSide1<<std::endl;
        }
            
        else 
            index++;
    }
    index = 0;
    for(auto & x : figuresPlayer2){
        if(x->mLetter == 'K'){
            indexOfKingSide2 = index;
            std::cout<<indexOfKingSide1<<std::endl;
        }
            
        else 
            index++;
    }
}
