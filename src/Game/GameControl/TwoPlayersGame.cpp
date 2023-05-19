#include "TwoPlayersGame.h"

TwoPlayersGame::TwoPlayersGame(std::shared_ptr<ApiBase> apiBase):GameControl(apiBase){
}


void TwoPlayersGame::startGameLoop(){

    Board::setPiecesOnBoard(g.piecesINplayer1, g.piecesINplayer2);
    
    bool gameRunning = true;

    while(gameRunning){
        //refresh UI
        apiBase -> update(g);
        
        //check game state
        checkDetected = kingIsInCheck(playingSide);
        if(checkDetected){
            checkMateDetected = isCheckMate(playingSide);
        }
        if(!checkDetected){
            stalemateDetected = isStalmate(playingSide);
        }

        //update UI if game state changed, (+ end if stalmate or check mate)
        if(checkMateDetected){
            apiBase -> handleGameEvent("CHECK MATE, PRESS ANY KEY TO END");
            return;
        }else if(checkDetected){
            apiBase -> handleGameEvent("CHECK");
        }else if(stalemateDetected){
            apiBase -> handleGameEvent("STALMATE");
            return;
        }
        
        //pick piece and position to move to
        std::pair< Coordinates,Coordinates > movementFromTo =  apiBase->pickPosition(playingSide, gameRunning);
        if(!gameRunning) break;
        
        //check whether move is OK, if not -> new iteration
        bool moveIsValid = g.moveIsValid(movementFromTo.first,movementFromTo.second);
        if( !moveIsValid) continue;
        if( Board::playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mPiece->mLetter == KING
        && !kingWillNotLandIntoCheck(movementFromTo.second, playingSide)){
            moveIsValid = false;
        }
        if(!moveIsValid) continue;

        //move is OK ... checking for en passant and castling
        g.addMoveToHistory(movementFromTo,b.playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mPiece);
        g.checkEnPassant(movementFromTo.second,movementFromTo.first);

        bool castleDetected = g.detectCastlingAttempt(movementFromTo.second, movementFromTo.first);
        if(castleDetected){
            bool succesfullyCasteled = g.castle(b, movementFromTo.second, movementFromTo.first);
            if(succesfullyCasteled){
                swapSides();
                continue;
            }else{
                continue;
            }
        }

        //checking if we are kicking out opponents piece
        if(g.checkIfPieceWasKickedOut(movementFromTo.second)){
            handleKickout(movementFromTo);
            if(gameIsOver) return;   
        }
        b.movePiece(movementFromTo.first, movementFromTo.second, true);
        //g.movesHistory.push_front(movementFromTo);

        //promote pawn if it is at the end
        if(!castleDetected){
            handlePawnPromotion(movementFromTo);
        }

        //updating game state
        stalemateDetected = isStalmate(playingSide);
        checkMateDetected = isCheckMate(playingSide);

        //end game if check mate 
        if(checkMateDetected){
            apiBase->update(g);
            apiBase->handleGameEvent("CHECK MATE, PRESS ANY KEY TO END");
            return;
        }
        swapSides();
    } 
    
    apiBase->saveGame(
            b,
            g,
            TWO_PLAYERS_GAME,
            0,
            checkDetected ? 1:0,
            checkMateDetected ? 1:0,
            stalemateDetected ? 1:0,
            playingSide
        );
}



void TwoPlayersGame::handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo){
    char letter = Board::playField[movementFromTo.second.mRowIndex][movementFromTo.second.mColumnIndex].mPiece
            ->mLetter;
    
    g.addMoveToHistory(movementFromTo,b.playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mPiece);
    g.kickout(movementFromTo.second, playingSide == 1 ? g.piecesOUTplayer2 : g.piecesOUTplayer1); 
    
    //end game if king was the target
    if(letter == KING){
        b.movePiece(movementFromTo.first, movementFromTo.second, true);
        apiBase->update(g);
        if(playingSide == 1){
            apiBase->handleGameEvent("GAME OVER , RED WINS, PRESS ANY KEY TO END");
        }else{
            apiBase->handleGameEvent("GAME OVER , BLUE WINS, PRESS ANY KEY TO END");
        }
        gameIsOver = true;
    }  
}

