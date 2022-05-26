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

GameControl::GameControl(){
    playingSide = 1;
    checkDetected = false;
    checkMateDetected = false;
    stalemateDetected = false; 
}

