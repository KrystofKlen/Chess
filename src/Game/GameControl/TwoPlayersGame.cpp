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
        checkGameState();
        handleChangedState();
        if(!gameRunning) return;
        
        //pick piece and position to move to
        std::pair< Coordinates,Coordinates > movementFromTo =  apiBase->pickPosition(playingSide, gameRunning);
        if(!gameRunning) break;
        
        //check whether move is OK, if not -> new iteration
        bool moveIsValid = validateMove(movementFromTo);
        if(!moveIsValid) continue; // let user to choose again

        //move is OK ... checking for en passant and castling
        g.addMoveToHistory(movementFromTo,b.playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mPiece);
        g.checkEnPassant(movementFromTo.second,movementFromTo.first);

        bool castleDetected = g.detectCastlingAttempt(movementFromTo.second, movementFromTo.first);
        if(castleDetected){
            bool succesfullyCasteled = g.castle(b, movementFromTo.second, movementFromTo.first);
            if(succesfullyCasteled){
                swapSides();
            }
            continue;
        }

        //checking if we are kicking out opponents piece
        if(g.checkIfPieceWasKickedOut(movementFromTo.second)){
            handleKickout(movementFromTo);
            if(!gameRunning) return;   
        }
        b.movePiece(movementFromTo.first, movementFromTo.second, true);

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
        gameRunning = false;
    }  
}

