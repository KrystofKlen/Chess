#include "../GameControl/GameStateController.h"

bool isCheckMate(Game & g, Board & b, int sidePlaying){

    std::shared_ptr<Figure> king;
    const std::list<std::shared_ptr<Figure>>* pOpponentFiguresIn;
    sidePlaying == 1 ? pOpponentFiguresIn =  &g.figuresINplayer2 : pOpponentFiguresIn = &g.figuresINplayer1;

    //find king
    for (int rowIndex = 0; rowIndex < 8; rowIndex++){
        for (int columnIndex = 0; columnIndex < 8; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mFigure->mLetter == 'K' && posRef.mFigure->mSide == sidePlaying){
                king = posRef.mFigure;
                rowIndex = 8;
                break;
            }
        }     
    }

    //check if king at his current position is in check
    if( !kingIsInCheck(g,b,sidePlaying)) return false;

    //generate moves for king
    std::list<Coordinates> movesKing;
    king->getPossibleMovePositions(movesKing);

    for(Coordinates & move : movesKing){
        if(kingWillNotLandIntoCheck(g,b,move,king)) return false;
    }


    std::list<Coordinates> moves;
    std::list<std::shared_ptr<Figure>>* pKingsFigures = 
    sidePlaying == 1 ? (pKingsFigures = &(g.figuresINplayer1)) : &g.figuresINplayer2;
    for(auto fig : *pKingsFigures){
        if(fig->mLetter!='K'){
            fig->getPossibleMovePositions(moves);
            for(auto & move : moves){
                if(fig->mCoordinates == move) continue;
                
                bool canKickOut = g.checkIfFigureWasKickedOut(move);
                std::shared_ptr<Figure> tmpKick;
                if(canKickOut){
                    tmpKick = Board::playField[move.mRowIndex][move.mColumnIndex].mFigure;
                    tmpKick->isInSimulation = false;
                }
                Coordinates previous = fig->mCoordinates;
                b.moveFigure(fig->mCoordinates, move, false);

                bool inCheck = kingIsInCheck(g,b,sidePlaying);

                b.moveFigure(move, previous, false);
                if(canKickOut){
                    Board::playField[move.mRowIndex][move.mColumnIndex].mFigure = tmpKick;
                    Board::playField[move.mRowIndex][move.mColumnIndex].mIsFree = false;
                    tmpKick->isInSimulation = true;
                } 

                if(!inCheck) return false;           
            }
        }        
    }
    return true;
}

bool isStalmate(Game & g, Board & b, int sidePlaying){

    std::shared_ptr<Figure> king;
    const std::list<std::shared_ptr<Figure>>* pFiguresIn;
    sidePlaying == 1 ? pFiguresIn =  &g.figuresINplayer1 : pFiguresIn = &g.figuresINplayer2;

    //find king
    for (int rowIndex = 0; rowIndex < 8; rowIndex++){
        for (int columnIndex = 0; columnIndex < 8; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mFigure->mLetter == 'K' && posRef.mFigure->mSide == sidePlaying){
                king = posRef.mFigure;
                rowIndex = 8;
                break;
            }
        }     
    }

    //no stalmate if king is in check
    if(kingIsInCheck(g,b,sidePlaying)) return false;

    //generate moves king 1
    std::list<Coordinates> movesKing;
    std::list<Coordinates> movesRest;
    king->getPossibleMovePositions(movesKing);

    for(Coordinates & move : movesKing){
        bool moveOK = kingWillNotLandIntoCheck(g, b,move, king);
        if(moveOK) return false;
    }

    //everywhere where king will go, he is gonna land into a check,
    //so we will check if there is another figure to make a move
    //if not -> stalmate detected
    for(auto & fig : *pFiguresIn){
        if(fig->mLetter!='K'){
            fig->getPossibleMovePositions(movesRest);
        }
        if(movesRest.size() > 0) return false;
    }

    return true;
}


bool kingIsInCheck(Game & g, Board & b, int sidePlaying){

    std::shared_ptr<Figure> king;
    const std::list<std::shared_ptr<Figure>>* pOpponentFiguresIn;
    sidePlaying == 1 ? pOpponentFiguresIn =  &g.figuresINplayer2 : pOpponentFiguresIn = &g.figuresINplayer1;

    //find king
    for (int rowIndex = 0; rowIndex < 8; rowIndex++){
        for (int columnIndex = 0; columnIndex < 8; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mFigure->mLetter == 'K' && posRef.mFigure->mSide == sidePlaying){
                king = posRef.mFigure;
                rowIndex = 8;
                break;
            }
        }     
    }

    //generate opponents moves
    std::list<Coordinates> opponentsMoves;
    for(auto & fig : *pOpponentFiguresIn){
        if(fig->isInSimulation){
            fig->getPossibleMovePositions(opponentsMoves);
        } 
    }

    for(Coordinates & move : opponentsMoves){
        if(move == king->mCoordinates){
            return true;
        }
    }

    return false;
}


bool kingWillNotLandIntoCheck( Game & g, Board & b, Coordinates & anticipatedPosition, std::shared_ptr<Figure> king ){

    Coordinates currentPosition = king->mCoordinates;
    int kingSide = king->mSide;

    Position & anticPosRef = Board::playField[anticipatedPosition.mRowIndex][anticipatedPosition.mColumnIndex];

    std::shared_ptr<Figure> tmpBackup = nullptr;

    //clear position if a opponents figure present, save info to tmp
    if(
       !anticPosRef.mIsFree &&
       anticPosRef.mFigure->mSide != kingSide
        ){
            tmpBackup = anticPosRef.mFigure;
        }

    //move king to anticipated position
    b.moveFigure(currentPosition, anticipatedPosition, false);

    std::list<Coordinates> opponentsMoves;
  
    //fill opponentsPossibleMoves
    for (int rowIndex = 0; rowIndex < 8; rowIndex++){
        for (int columnIndex = 0; columnIndex < 8; columnIndex++){
            
            const Position & curPosRef = Board::playField[rowIndex][columnIndex];
            if( !curPosRef.mIsFree && kingSide != curPosRef.mFigure->mSide ){

                if(curPosRef.mFigure->mLetter == 'P'){
                    curPosRef.mFigure->mSide == 1 ? 
                    addPawnPossibleKickoutsSide1(opponentsMoves, *curPosRef.mFigure) 
                    : addPawnPossibleKickoutsSide2(opponentsMoves, *curPosRef.mFigure);
                }else{
                    curPosRef.mFigure->getPossibleMovePositions(opponentsMoves);
                }

            }
        }  
        
    }

    //move king back
    b.moveFigure(anticipatedPosition, currentPosition, false);

    //reset position the king was at
    anticPosRef.mFigure = tmpBackup;
    if(tmpBackup != nullptr)
        anticPosRef.mIsFree = false;

    //find at discovered position if opponent can target king
    for(Coordinates opponentsMove : opponentsMoves){
        if(opponentsMove == anticipatedPosition){  
            return false;
        }
    }
    
    return true;
}

bool kingWillNotLandIntoCheck( Game & g, Board & b, Coordinates & anticipatedPosition, int sidePlaying ){

    std::shared_ptr<Figure> king;

    //find king
    for (int rowIndex = 0; rowIndex < 8; rowIndex++){
        for (int columnIndex = 0; columnIndex < 8; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mFigure->mLetter == 'K' && posRef.mFigure->mSide == sidePlaying){
                king = posRef.mFigure;
                rowIndex = 8;
                break;
            }
        }     
    }

    return kingWillNotLandIntoCheck(g,b, anticipatedPosition, king);
}