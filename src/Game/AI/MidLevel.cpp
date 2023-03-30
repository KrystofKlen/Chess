#include "MidLevel.h"
#include<iostream>

void MidLevel::makeNextMove(Game & g, Board & b, bool & pcWin){
    std::pair<Coordinates, Coordinates> highestRankMove = { {-1,-1}, {-1,-1}  };
    getHighestRankMove(g,highestRankMove);
    
    if(g.checkIfPieceWasKickedOut(highestRankMove.second)){
        kickoutByComputer(g,pcWin,highestRankMove.second);
    }

    b.movePiece(highestRankMove.first, highestRankMove.second, true);
    
}

MidLevel::MidLevel() {
    srand(time(NULL));
}