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

bool GameControl::isCheckMate(int sidePlaying){

    std::shared_ptr<Piece> king;
    const std::list<std::shared_ptr<Piece>>* pOpponentPiecesIn;
    sidePlaying == 1 ? pOpponentPiecesIn =  &g.piecesINplayer2 : pOpponentPiecesIn = &g.piecesINplayer1;

    //find king
    for (int rowIndex = 0; rowIndex < Board::BOARD_SIZE; rowIndex++){
        for (int columnIndex = 0; columnIndex < Board::BOARD_SIZE; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mPiece->mLetter == KING && posRef.mPiece->mSide == sidePlaying){
                king = posRef.mPiece;
                rowIndex = Board::BOARD_SIZE;
                break;
            }
        }     
    }
    //findKing(king,sidePlaying);

    //check if king at his current position is in check
    if( !kingIsInCheck(sidePlaying)) return false;

    //generate moves for king
    std::list<Coordinates> movesKing;
    king->getPossibleMovePositions(movesKing);

    for(Coordinates & move : movesKing){
        if(kingWillNotLandIntoCheck(move,king)) return false;
    }


    std::list<Coordinates> moves;
    std::list<std::shared_ptr<Piece>>* pKingsPieces = 
    sidePlaying == 1 ? (pKingsPieces = &(g.piecesINplayer1)) : &g.piecesINplayer2;
    for(auto fig : *pKingsPieces){
        if(fig->mLetter!=KING){
            fig->getPossibleMovePositions(moves);
            for(auto & move : moves){
                if(fig->mCoordinates == move) continue;
                
                bool canKickOut = g.checkIfPieceWasKickedOut(move);
                std::shared_ptr<Piece> tmpKick;
                if(canKickOut){
                    tmpKick = Board::playField[move.mRowIndex][move.mColumnIndex].mPiece;
                    tmpKick->isInSimulation = false;
                }
                Coordinates previous = fig->mCoordinates;
                b.movePiece(fig->mCoordinates, move, false);

                bool inCheck = kingIsInCheck(sidePlaying);

                b.movePiece(move, previous, false);
                if(canKickOut){
                    Board::playField[move.mRowIndex][move.mColumnIndex].mPiece = tmpKick;
                    Board::playField[move.mRowIndex][move.mColumnIndex].mIsFree = false;
                    tmpKick->isInSimulation = true;
                } 

                if(!inCheck) return false;           
            }
        }        
    }
    return true;
}

bool GameControl::isStalmate(int sidePlaying){

    std::shared_ptr<Piece> king;
    const std::list<std::shared_ptr<Piece>>* pPiecesIn;
    sidePlaying == 1 ? pPiecesIn =  &g.piecesINplayer1 : pPiecesIn = &g.piecesINplayer2;

    //find king
    for (int rowIndex = 0; rowIndex < Board::BOARD_SIZE; rowIndex++){
        for (int columnIndex = 0; columnIndex < Board::BOARD_SIZE; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mPiece->mLetter == KING && posRef.mPiece->mSide == sidePlaying){
                king = posRef.mPiece;
                rowIndex = Board::BOARD_SIZE;
                break;
            }
        }     
    }

    //no stalmate if king is in check
    if(kingIsInCheck(sidePlaying)) return false;

    //generate moves king 1
    std::list<Coordinates> movesKing;
    std::list<Coordinates> movesRest;
    king->getPossibleMovePositions(movesKing);

    for(Coordinates & move : movesKing){
        bool moveOK = kingWillNotLandIntoCheck(move, king);
        if(moveOK) return false;
    }

    //everywhere where king will go, he is gonna land into a check,
    //so we will check if there is another piece to make a move
    //if not -> stalmate detected
    for(auto & fig : *pPiecesIn){
        if(fig->mLetter!=KING){
            fig->getPossibleMovePositions(movesRest);
        }
        if(movesRest.size() > 0) return false;
    }

    return true;
}


bool GameControl::kingIsInCheck(int sidePlaying){

    std::shared_ptr<Piece> king;
    const std::list<std::shared_ptr<Piece>>* pOpponentPiecesIn;
    sidePlaying == 1 ? pOpponentPiecesIn =  &g.piecesINplayer2 : pOpponentPiecesIn = &g.piecesINplayer1;

    //find king
    for (int rowIndex = 0; rowIndex < Board::BOARD_SIZE; rowIndex++){
        for (int columnIndex = 0; columnIndex < Board::BOARD_SIZE; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mPiece->mLetter == KING && posRef.mPiece->mSide == sidePlaying){
                king = posRef.mPiece;
                rowIndex = Board::BOARD_SIZE;
                break;
            }
        }     
    }

    //generate opponents moves
    std::list<Coordinates> opponentsMoves;
    for(auto & fig : *pOpponentPiecesIn){
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


bool GameControl::kingWillNotLandIntoCheck( Coordinates & anticipatedPosition, std::shared_ptr<Piece> king ){

    Coordinates currentPosition = king->mCoordinates;
    int kingSide = king->mSide;

    Position & anticPosRef = Board::playField[anticipatedPosition.mRowIndex][anticipatedPosition.mColumnIndex];

    std::shared_ptr<Piece> tmpBackup = nullptr;

    //clear position if a opponents piece present, save info to tmp
    if(
       !anticPosRef.mIsFree &&
       anticPosRef.mPiece->mSide != kingSide
        ){
            tmpBackup = anticPosRef.mPiece;
        }

    //move king to anticipated position
    b.movePiece(currentPosition, anticipatedPosition, false);

    std::list<Coordinates> opponentsMoves;
  
    //fill opponentsPossibleMoves
    for (int rowIndex = 0; rowIndex < Board::BOARD_SIZE; rowIndex++){
        for (int columnIndex = 0; columnIndex < Board::BOARD_SIZE; columnIndex++){
            
            const Position & curPosRef = Board::playField[rowIndex][columnIndex];
            if( !curPosRef.mIsFree && kingSide != curPosRef.mPiece->mSide ){

                if(curPosRef.mPiece->mLetter == PAWN){
                    curPosRef.mPiece->mSide == 1 ? 
                    addPawnPossibleKickoutsSide1(opponentsMoves, *curPosRef.mPiece) 
                    : addPawnPossibleKickoutsSide2(opponentsMoves, *curPosRef.mPiece);
                }else{
                    curPosRef.mPiece->getPossibleMovePositions(opponentsMoves);
                }

            }
        }    
    }

    //move king back
    b.movePiece(anticipatedPosition, currentPosition, false);

    //reset position the king was at
    anticPosRef.mPiece = tmpBackup;
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

bool GameControl::kingWillNotLandIntoCheck( Coordinates & anticipatedPosition, int sidePlaying ){

    std::shared_ptr<Piece> king;

    //find king
    for (int rowIndex = 0; rowIndex < Board::BOARD_SIZE; rowIndex++){
        for (int columnIndex = 0; columnIndex < Board::BOARD_SIZE; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if( !posRef.mIsFree && posRef.mPiece->mLetter == KING && posRef.mPiece->mSide == sidePlaying){
                king = posRef.mPiece;
                rowIndex = Board::BOARD_SIZE;
                break;
            }
        }     
    }
   // findKing(king,sidePlaying);

    return kingWillNotLandIntoCheck(anticipatedPosition, king);
}

void GameControl::checkGameState(){
    //check game state
    checkDetected = kingIsInCheck(playingSide);
    if(checkDetected){
        checkMateDetected = isCheckMate(playingSide);
    }
    if(!checkDetected){
        stalemateDetected = isStalmate(playingSide);
    }
}

void GameControl::handleChangedState(){
    //update UI if game state changed, (+ end if stalmate or check mate)
    if(checkMateDetected){
        apiBase -> handleGameEvent("CHECK MATE, PRESS ANY KEY TO END");
        gameRunning = false;
        return;
    }else if(checkDetected){
        apiBase -> handleGameEvent("CHECK");
        return;
    }else if(stalemateDetected){
        apiBase -> handleGameEvent("STALMATE");
        gameRunning = false;
        return;
    }
}

bool GameControl::validateMove(std::pair<Coordinates, Coordinates> movementFromTo){
    //check whether move is OK, if not -> new iteration
    bool moveIsValid = g.moveIsValid(movementFromTo.first,movementFromTo.second);
    if(!moveIsValid) return false;
    if( Board::playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mPiece->mLetter == KING
    && !kingWillNotLandIntoCheck(movementFromTo.second, playingSide))
        moveIsValid = false;
    if(!moveIsValid) return false;

    return true;
}
