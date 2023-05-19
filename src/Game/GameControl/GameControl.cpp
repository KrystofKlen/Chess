#include "GameControl.h"

void GameControl::swapSides(){
    if(playingSide == 1)
        playingSide = 2;
    else playingSide = 1;
}

void GameControl::setGameState(bool isCheck, bool isStalmate, bool isCheckMate, int playingSide){
    checkDetected = isCheck;
    stalemateDetected = isStalmate;
    checkMateDetected = isCheckMate;
    this->playingSide = playingSide;
}

GameControl::GameControl(std::shared_ptr<ApiBase> apiBase){
    this->apiBase = apiBase;
    playingSide = 1;
    checkDetected = false;
    checkMateDetected = false;
    stalemateDetected = false; 
}

void GameControl::handlePawnPromotion(const std::pair< Coordinates,Coordinates > & movementFromTo){
    bool pawnAtEnd = g.checkIfPawnReachedEnd(playingSide);
    if(pawnAtEnd){
        apiBase->promotePawn(movementFromTo.second,  g,b);
    }
}



