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

    // return if depth == 0 -- botom of decision tree reached   
    if(depth == 0){
        return  evaluetePlayField(g);
    } 
    
    if(maxSearch){  
        //player 1 searches maximum
        int maxFound = -1000000000;
        // loop all pieces in game
        for(auto & fig : g.piecesINplayer1){
            if(!fig->isInSimulation) continue;
            std::list<Coordinates> moves;
            
            fig->getPossibleMovePositions(moves);
            for(auto & move : moves){
                if(fig->mCoordinates == move) continue;
                int evaluation = evaluateMove(g,b,fig,move,maxSearch,depth,movesRank);           
                if(evaluation > maxFound){
                    maxFound = evaluation;
                }
            }
        }
        return maxFound;
    }
    //player 2 (PC) searches minimum
    else{
        int minFound = 1000000000;
        // loop all pieces in game
        for(auto & fig : g.piecesINplayer2){
            if(!fig->isInSimulation) continue;
            std::list<Coordinates> moves;
            fig->getPossibleMovePositions(moves);
            for(auto & move : moves){
                if(fig->mCoordinates == move) continue;
                int evaluation = evaluateMove(g,b,fig,move,maxSearch,depth,movesRank);
                if(depth == MIN_MAX_DEPTH){
                    movesRank.push_back ({ evaluation,{fig->mCoordinates, move}});
                }
                if(evaluation < minFound){
                    minFound = evaluation;
                }
            }            
        }
        return minFound;
    }
}


void DifficultLevel::makeNextMove(Game & g, Board & b, bool & pcWin){
    
    std::list<std::pair<int, std::pair<Coordinates, Coordinates>>>  movesRank;

    //evaluating moves
    minMax(g,b,false,MIN_MAX_DEPTH, movesRank);

    std::pair<Coordinates, Coordinates> bestMove;

    //looking for min
    int minRank = 1000000000;
    std::vector<std::pair<Coordinates, Coordinates>> equalMoves;
    for(auto & move : movesRank){
        if(move.first == minRank){
            equalMoves.push_back(move.second);
        }else if (move.first < minRank){
            equalMoves.clear();
            equalMoves.push_back(move.second);
            minRank = move.first;
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

    g.addMoveToHistory(
        bestMove,
        b.playField[bestMove.first.mRowIndex][bestMove.first.mColumnIndex].mPiece);
    
    b.refreshPieceCoordinates();
    
    if(g.checkIfPieceWasKickedOut(bestMove.second)){
        kickoutByComputer(g,pcWin, bestMove.second);
    }
    
    b.movePiece(bestMove.first, bestMove.second, true);
}

int DifficultLevel::evaluetePlayField(Game& g){

    int rankPlayer1After = 0;
    int rankPlayer2After = 0;

    //counting ranksAfter at the end of minmax
    for(int rowIndex = 0; rowIndex<Board::BOARD_SIZE; rowIndex++){
        for(int columnIndex = 0; columnIndex<Board::BOARD_SIZE; columnIndex++ ){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if(!posRef.mIsFree)
                posRef.mPiece->mSide == 1 ? rankPlayer1After += posRef.mPiece->mRank : rankPlayer2After += posRef.mPiece->mRank;
        }
    }

    int rankPlayer1Before = 0;
    int rankPlayer2Before = 0;

    //counting ranks before minMax
    for(auto & x : g.piecesINplayer1){
        rankPlayer1Before += x->mRank;
    }
    for(auto & x : g.piecesINplayer2){
        rankPlayer2Before += x->mRank;
    }
    
    int diffPlayer1 = rankPlayer1Before - rankPlayer1After;
    int diffPlayer2 = rankPlayer2Before - rankPlayer2After;

    //player 1 -> MAX, player 2-> MIN
    return diffPlayer1 - diffPlayer2;
}

int DifficultLevel::evaluateImportanceOfKickedPiece(std::shared_ptr<Piece> & kickedPiece){
    return 10 * kickedPiece->mRank;
}

int DifficultLevel::evaluateMove(Game &g, Board &b, std::shared_ptr<Piece> &fig, const Coordinates &move, bool maxSearch, int depth, std::list<std::pair<int, std::pair<Coordinates, Coordinates>>> &movesRank){
    int evaluation = 0;
    bool canKickOut = g.checkIfPieceWasKickedOut(move);

    std::shared_ptr<Piece> tmpKick;
    if(canKickOut){
        temporarilyKickOut(tmpKick,move);
        int importanceOfKickedPiece = evaluateImportanceOfKickedPiece(tmpKick);
        evaluation += maxSearch ? importanceOfKickedPiece : (-1)*importanceOfKickedPiece;
    }
    // save coordinates of piece, so that it can be put back, when we return from recursive calls
    Coordinates previous = fig->mCoordinates;
    b.movePiece(fig->mCoordinates, move, false);
    // explore options with recursion
    evaluation += minMax(g,b,!maxSearch,depth - 1,movesRank);

    //move back
    b.movePiece(move, previous, false);
    if(canKickOut){
        returnTemporarilyKickedPiece(tmpKick,move);
    }
    return evaluation;
}

void DifficultLevel::temporarilyKickOut(std::shared_ptr<Piece> & kickedPiece, Coordinates move){
    kickedPiece = Board::playField[move.mRowIndex][move.mColumnIndex].mPiece;
    kickedPiece->isInSimulation = false;
}

void DifficultLevel::returnTemporarilyKickedPiece(std::shared_ptr<Piece> & kickedPiece, Coordinates to){
    Board::playField[to.mRowIndex][to.mColumnIndex].mPiece = kickedPiece;
    Board::playField[to.mRowIndex][to.mColumnIndex].mPiece->mCoordinates = {to.mRowIndex, to.mColumnIndex};
    Board::playField[to.mRowIndex][to.mColumnIndex].mIsFree = false;
    kickedPiece->isInSimulation = true;
}

DifficultLevel::DifficultLevel(){
    srand (time(NULL));
}

