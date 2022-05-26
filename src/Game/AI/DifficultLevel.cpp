#include <limits>
#include "DifficultLevel.h"
#include <iostream>

int DifficultLevel::minMax(
    Game & g, 
    Board & b, 
    bool maxSearch,
    int depth,
    std::list<std::pair<int, std::pair<Coordinates, Coordinates>>> & movesRank
    )
    {
    if(depth == 0){
        return  evaluetePlayField(g);
    } 
    
    //player 1 searches maximum
    int maxFound = -1000000000;
    if(maxSearch){  
        // loop all figures in game
        for(auto & fig : g.figuresINplayer1){
            if(!fig->isInSimulation) continue;
            std::list<Coordinates> moves;
            
            fig->getPossibleMovePositions(moves);
            for(auto & move : moves){
                if(fig->mCoordinates == move) continue;
                
                int evaluation = 0;
                bool canKickOut = g.checkIfFigureWasKickedOut(move);
                std::shared_ptr<Figure> tmpKick;
                if(canKickOut){
                    tmpKick = Board::playField[move.mRowIndex][move.mColumnIndex].mFigure;
                    tmpKick->isInSimulation = false;
                        evaluation += 10*tmpKick->mRank;
                }
                Coordinates previous = fig->mCoordinates;
                b.moveFigure(fig->mCoordinates, move, false);

                evaluation += minMax(g,b,!maxSearch,depth - 1,movesRank);

                b.moveFigure(move, previous, false);
                if(canKickOut){
                    Board::playField[move.mRowIndex][move.mColumnIndex].mFigure = tmpKick;
                    Board::playField[move.mRowIndex][move.mColumnIndex].mIsFree = false;
                    tmpKick->isInSimulation = true;
                }               

                if(evaluation > maxFound){
                    maxFound = evaluation;
                }
            }
            
        }
        return maxFound;
    }
    //player 2 (PC) searches minimum
    else{
        // loop all figures in game
        int minFound = 1000000000;
        for(auto & fig : g.figuresINplayer2){
            if(!fig->isInSimulation) continue;
            std::list<Coordinates> moves;
            fig->getPossibleMovePositions(moves);
            std::shared_ptr<Figure> tmpKick;
            for(auto & move : moves){
                if(fig->mCoordinates == move) continue;

                int evaluation = 0;
                bool canKickOut = g.checkIfFigureWasKickedOut(move);
                if(canKickOut){
                    tmpKick = Board::playField[move.mRowIndex][move.mColumnIndex].mFigure;
                    tmpKick->isInSimulation = false;
                    evaluation -= 10*tmpKick->mRank;
                }
                Coordinates previous = fig->mCoordinates;
                
                b.moveFigure(fig->mCoordinates, move, false);

                evaluation += minMax(g,b,!maxSearch,depth - 1,movesRank);

                //move back
                b.moveFigure(move, previous, false);
                if(canKickOut){
                    Board::playField[move.mRowIndex][move.mColumnIndex].mFigure = tmpKick;
                    Board::playField[move.mRowIndex][move.mColumnIndex].mFigure->mCoordinates = {move.mRowIndex, move.mColumnIndex};
                    Board::playField[move.mRowIndex][move.mColumnIndex].mIsFree = false;
                    tmpKick->isInSimulation = true;
                }

                if(depth == 3){
                    movesRank.push_back ({ evaluation,{fig->mCoordinates, move}});
                }
               // Board::playField[move.mRowIndex][move.mColumnIndex].mFigure->isInSimulation = true;
                if(evaluation < minFound){
                    minFound = evaluation;
                }
            }            
        }
        return minFound;
    }
}

void DifficultLevel::makeNextMove(Game & g, Board & b, bool & pcWin){
    
    std::vector<std::pair<int, Coordinates>> vctRankMoves;
    
    std::pair<Coordinates,Coordinates> bm;

    std::list<std::pair<int, std::pair<Coordinates, Coordinates>>>  movesRank;

    //evaluating moves
    minMax(g,b,false,3, movesRank);

    std::pair<Coordinates, Coordinates> bestMove;

    //looking for min
    int minRank = 1000000000;
    std::vector<std::pair<Coordinates, Coordinates>> equalMoves;
    for(auto & x : movesRank){
        if(x.first == minRank){
            equalMoves.push_back(x.second);
        }else if (x.first < minRank){
            equalMoves.clear();
            equalMoves.push_back(x.second);
            minRank = x.first;
        }
    }   

    bool bestMoveSelected = false;
    
    //selecting the best move from moves with the lowest rank
    while(!bestMoveSelected){
        int randomIndex = rand() % (equalMoves.size());
        if(g.moveIsValid(equalMoves[randomIndex].first, equalMoves[randomIndex].second))
        bestMove = equalMoves[randomIndex];
        bestMoveSelected = true;
    }
    
    b.refreshFigureCoordinates();
    
    if(g.checkIfFigureWasKickedOut(bestMove.second)){
        kickoutByComputer(g,pcWin, bestMove.second);
    }
    b.moveFigure(bestMove.first, bestMove.second, true);
}

int DifficultLevel::evaluetePlayField(Game& g){

    int rankPlayer1After = 0;
    int rankPlayer2After = 0;

    //counting ranksAfter at the end of minmax
    for(int rowIndex = 0; rowIndex<8; rowIndex++){
        for(int columnIndex = 0; columnIndex<8; columnIndex++ ){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if(!posRef.mIsFree)
                posRef.mFigure->mSide == 1 ? rankPlayer1After += posRef.mFigure->mRank : rankPlayer2After += posRef.mFigure->mRank;
        }
    }

    int rankPlayer1Before = 0;
    int rankPlayer2Before = 0;

    //counting ranks before minMax
    for(auto & x : g.figuresINplayer1){
        rankPlayer1Before += x->mRank;
    }
    for(auto & x : g.figuresINplayer2){
        rankPlayer2Before += x->mRank;
    }
    
    int diffPlayer1 = rankPlayer1Before - rankPlayer1After;
    int diffPlayer2 = rankPlayer2Before - rankPlayer2After;

    //player 1 -> MAX, player 2-> MIN
    return diffPlayer1 - diffPlayer2;
}

DifficultLevel::DifficultLevel(){
    srand (time(NULL));
}

