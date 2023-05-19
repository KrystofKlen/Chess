#include "OnePlayerGame.h"

OnePlayerGame::OnePlayerGame(int difficulty, std::shared_ptr<ApiBase> apiBase):GameControl(apiBase){
    mDifficulty = difficulty;
    if(difficulty == EASY_LEVEL){
        ptrComputer = std::make_unique<EasyLevel>();
    }else if(difficulty == MID_LEVEL){
        ptrComputer = std::make_unique<MidLevel>();
    }else{
        ptrComputer = std::make_unique<DifficultLevel>();
    }
}

void OnePlayerGame::startGameLoop(){
    
    Board::setPiecesOnBoard(g.piecesINplayer1, g.piecesINplayer2);
    
    while(gameRunning){
        b.refreshPieceCoordinates();

        //refresh UI
        apiBase->update(g);

        checkGameState();
        b.refreshPieceCoordinates();
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
            if(!succesfullyCasteled){
                continue;
            }
        }

        //checking if we are kicking out opponents piece
        if(g.checkIfPieceWasKickedOut(movementFromTo.second) && !castleDetected){
            handleKickout(movementFromTo);  
            if(!gameRunning) return;    
        }
        if(!castleDetected){
            b.movePiece(movementFromTo.first, movementFromTo.second, false);
        }
            
        //promote pawn if it is at the end
        if(!castleDetected){
            handlePawnPromotion(movementFromTo);
            if(!gameRunning) return;   
        }

        //updating game state
        stalemateDetected = isStalmate(playingSide);
        checkMateDetected = isCheckMate(playingSide);

        b.refreshPieceCoordinates();
        //no stalmate or check mate -> pc can make a move
        if( !stalemateDetected && !checkMateDetected ){
            makeMoveForPC();
            if(!gameRunning) return;
        } 
    } 
    
    apiBase->saveGame(
        b,
        g,
        ONE_PLAYER_GAME,
        mDifficulty,
        checkDetected ? 1:0,
        checkMateDetected ? 1:0,
        stalemateDetected ? 1:0,
        playingSide
    );
}

void OnePlayerGame::handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo){
    char letter = Board::playField[movementFromTo.second.mRowIndex][movementFromTo.second.mColumnIndex].mPiece
            ->mLetter;
            
    g.kickout(movementFromTo.second, g.piecesOUTplayer2);
    
    //end game if king was the target
    if(letter == KING){
        b.movePiece(movementFromTo.first, movementFromTo.second, true);
        apiBase->update(g);
        apiBase->handleGameEvent("GAME OVER , RED WINS, PRESS ANY KEY TO END");
        gameRunning = false;
    }      
}

void OnePlayerGame::makeMoveForPC(){
    bool pcWin = false;
    ptrComputer->makeNextMove(g, b, pcWin);

    if(pcWin){
        apiBase->update(g);
        apiBase->handleGameEvent("GAME OVER , RED WINS, PRESS ANY KEY TO END");
        gameRunning = false;
    }
}
