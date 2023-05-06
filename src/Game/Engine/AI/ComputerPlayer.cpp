#include "ComputerPlayer.h"


void ComputerPlayer::generateAllMoves(Game & g, std::vector<std::pair<Coordinates, Coordinates>> & allPossibleMoves){
    for(auto & x : g.piecesINplayer2){
        std::list<Coordinates> possibleMovesForPiece;
        x->getPossibleMovePositions(possibleMovesForPiece);
        for(Coordinates possibleMove : possibleMovesForPiece){
            allPossibleMoves.push_back( { x.get()->mCoordinates, possibleMove } );
        }
    }
}

 void ComputerPlayer::getHighestRankMove( Game & g,std::pair<Coordinates, Coordinates>  & move){
     int highestRank = 0;
     std::vector<std::pair<Coordinates, Coordinates>> allPossibleMoves;
     
     for(auto & x : g.piecesINplayer2){
         std::list<Coordinates> possibleMovesForPiece;
         x->getPossibleMovePositions(possibleMovesForPiece);
         for(Coordinates possibleMove : possibleMovesForPiece){
            allPossibleMoves.push_back( { x.get()->mCoordinates, possibleMove } );
            const Position & posRef = Board::playField[possibleMove.mRowIndex][possibleMove.mColumnIndex];
            if( !posRef.mIsFree && posRef.mPiece->mRank > highestRank){
                move = { x->mCoordinates, possibleMove };
                highestRank = posRef.mPiece->mRank;
            }
        } 
          
     }

     if(highestRank == 0){
         //we can not kickout any piece, so we will pick a random move
         int randomIndex = rand() % (allPossibleMoves.size() - 1);
         move = allPossibleMoves[randomIndex];
     }
 }

 void ComputerPlayer::kickoutByComputer(Game & g, bool & pcWin, const Coordinates & to){
    char letter = Board::playField[to.mRowIndex][to.mColumnIndex]
    .mPiece->mLetter;
    g.kickout(to, g.piecesOUTplayer1);  
    if(letter == KING){
        pcWin = true;
        return;
    }
}