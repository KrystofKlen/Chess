#include "ComputerPlayer.h"


void ComputerPlayer::generateAllMoves(Game & g, std::vector<std::pair<Coordinates, Coordinates>> & allPossibleMoves){
    for(auto & x : g.figuresINplayer2){
        std::list<Coordinates> possibleMovesForFigure;
        x->getPossibleMovePositions(possibleMovesForFigure);
        for(Coordinates possibleMove : possibleMovesForFigure){
            allPossibleMoves.push_back( { x.get()->mCoordinates, possibleMove } );
        }
    }
}

 void ComputerPlayer::getHighestRankMove( Game & g,std::pair<Coordinates, Coordinates>  & move){
     int highestRank = 0;
     std::vector<std::pair<Coordinates, Coordinates>> allPossibleMoves;
     
     for(auto & x : g.figuresINplayer2){
         std::list<Coordinates> possibleMovesForFigure;
         x->getPossibleMovePositions(possibleMovesForFigure);
         for(Coordinates possibleMove : possibleMovesForFigure){
            allPossibleMoves.push_back( { x.get()->mCoordinates, possibleMove } );
            const Position & posRef = Board::playField[possibleMove.mRowIndex][possibleMove.mColumnIndex];
            if( !posRef.mIsFree && posRef.mFigure->mRank > highestRank){
                move = { x->mCoordinates, possibleMove };
                highestRank = posRef.mFigure->mRank;
            }
        } 
          
     }

     if(highestRank == 0){
         //we can not kickout any figure, so we will pick a random move
         int randomIndex = rand() % (allPossibleMoves.size() - 1);
         move = allPossibleMoves[randomIndex];
     }
 }

 void ComputerPlayer::kickoutByComputer(Game & g, bool & pcWin, const Coordinates & to){
    char letter = Board::playField[to.mRowIndex][to.mColumnIndex]
    .mFigure->mLetter;
    g.kickout(to, g.figuresOUTplayer1);  
    if(letter == 'K'){
        pcWin = true;
        return;
    }
}