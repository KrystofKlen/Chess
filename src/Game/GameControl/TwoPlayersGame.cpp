#include "TwoPlayersGame.h"

void TwoPlayersGame::startGameLoop(){

    Board::setPiecesOnBoard(g.piecesINplayer1, g.piecesINplayer2);
    
    bool gameRunning = true;

    while(gameRunning){
        //refresh UI
        api.showBoard();
        api.showMovesHistory(g.getMovesHistory());
        api.updatePieces(g);

        //checkDetected = false;
        //check game state
        checkDetected = kingIsInCheck(g,b,playingSide);
        if(checkDetected){
            checkMateDetected = isCheckMate(g,b,playingSide);
        }
        if(!checkDetected){
            stalemateDetected = isStalmate(g,b,playingSide);
        }

        //update UI if game state changed, (+ end if stalmate or check mate)
        if(checkMateDetected){
            api.showAlert("CHECK MATE, PRESS ANY KEY TO END");
            return;
        }else if(checkDetected){
            api.showAlert("CHECK");
        }else if(stalemateDetected){
            api.showAlert("STALMATE");
            return;
        }
        
        //pick piece and position to move to
        std::pair< Coordinates,Coordinates > movementFromTo =  api.pickPosition(playingSide, gameRunning);
        if(!gameRunning) break;
        
        //check whether move is OK, if not -> new iteration
        bool moveIsValid = g.moveIsValid(movementFromTo.first,movementFromTo.second);
        if( !moveIsValid) continue;
        if( Board::playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mPiece->mLetter == 'K'
        && !kingWillNotLandIntoCheck(g,b, movementFromTo.second, playingSide)){
            moveIsValid = false;
        }
        if(!moveIsValid) continue;

        //move is OK ... checking for en passant and castling
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
            char letter = Board::playField[movementFromTo.second.mRowIndex][movementFromTo.second.mColumnIndex].mPiece
            ->mLetter;
            g.kickout(movementFromTo.second, playingSide == 1 ? g.piecesOUTplayer2 : g.piecesOUTplayer1); 
            
            //end game if king was the target
            if(letter == 'K'){
                b.movePiece(movementFromTo.first, movementFromTo.second, true);
                api.showBoard();
                api.showMovesHistory(g.getMovesHistory());
                api.updatePieces(g);
                if(playingSide == 1){
                    api.showAlert("GAME OVER , RED WINS, PRESS ANY KEY TO END");
                }else{
                    api.showAlert("GAME OVER , BLUE WINS, PRESS ANY KEY TO END");
                }
                return;
            }     
        }
        b.movePiece(movementFromTo.first, movementFromTo.second, true);
        //g.movesHistory.push_front(movementFromTo);

        //promote pawn if it is at the end
        bool pawnAtEnd = g.checkIfPawnReachedEnd(playingSide);
        if(pawnAtEnd){
            api.promotePawn(movementFromTo.second,  g,b);
        }

        //updating game state
        checkMateDetected = isCheckMate(g,b, playingSide);

        //end game if check mate 
        if(checkMateDetected){
            api.showBoard();
            api.showMovesHistory(g.getMovesHistory());
            api.updatePieces(g);
            api.showAlert("CHECK MATE, PRESS ANY KEY TO END");
            return;
        }
        swapSides();
    } 
    
    
    // api.saveGame(
    //     b,
    //     g,
    //     "2",
    //     "0",
    //     checkDetected ? "1" : "0",
    //     checkMateDetected ? "1" : "0",
    //     stalemateDetected ? "1" : "0",
    //     std::to_string(playingSide) 
    //     );
    api.saveGame2(
            b,
            g,
            2,
            0,
            checkDetected ? 1:0,
            checkMateDetected ? 1:0,
            stalemateDetected ? 1:0,
            playingSide
        );
}

