#include "MidLevel.h"
#include<iostream>

void MidLevel::makeNextMove(Game & g, Board & b, bool & pcWin){
    std::pair<Coordinates, Coordinates> highestRankMove = { {-1,-1}, {-1,-1}  };
    getHighestRankMove(g,highestRankMove);
    
    if(g.checkIfPieceWasKickedOut(highestRankMove.second)){
        kickoutByComputer(g,pcWin,highestRankMove.second);
    }

    g.addMoveToHistory({highestRankMove.first, highestRankMove.second},
    Board::playField[highestRankMove.first.mRowIndex][highestRankMove.first.mColumnIndex].mPiece);
    b.movePiece(highestRankMove.first, highestRankMove.second, true);
    
}

MidLevel::MidLevel() {
    srand(time(NULL));
}