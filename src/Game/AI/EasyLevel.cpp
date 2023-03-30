#include "EasyLevel.h"

void EasyLevel::makeNextMove(Game & g, Board & b, bool & pcWin){
    std::vector<std::pair<Coordinates, Coordinates>> allPossibleMoves;
    generateAllMoves(g, allPossibleMoves);
    int randomIndex = rand() % (allPossibleMoves.size() - 1);
    
    if(g.checkIfPieceWasKickedOut(allPossibleMoves[randomIndex].second)){
        kickoutByComputer(g,pcWin,allPossibleMoves[randomIndex].second);  
    }
    b.movePiece(allPossibleMoves[randomIndex].first, allPossibleMoves[randomIndex].second, true);
}

EasyLevel::EasyLevel(){
    srand (time(NULL));
}