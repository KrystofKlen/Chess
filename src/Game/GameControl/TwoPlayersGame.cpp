#include "TwoPlayersGame.h"

void TwoPlayersGame::startGameLoop(){

    Board::setFiguresOnBoard(g.figuresINplayer1, g.figuresINplayer2);
    
    bool gameRunning = true;

    while(gameRunning){
        //refresh UI
        api.showBoard();
        api.updateFigures(g);

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
        
        //pick figure and position to move to
        std::pair< Coordinates,Coordinates > movementFromTo =  api.pickPosition(playingSide, gameRunning);
        if(!gameRunning) break;
        
        //check whether move is OK, if not -> new iteration
        bool moveIsValid = g.moveIsValid(movementFromTo.first,movementFromTo.second);
        if( !moveIsValid) continue;
        if( Board::playField[movementFromTo.first.mRowIndex][movementFromTo.first.mColumnIndex].mFigure->mLetter == 'K'
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

        //checking if we are kicking out opponents figure
        if(g.checkIfFigureWasKickedOut(movementFromTo.second)){
            char letter = Board::playField[movementFromTo.second.mRowIndex][movementFromTo.second.mColumnIndex].mFigure
            ->mLetter;
            g.kickout(movementFromTo.second, playingSide == 1 ? g.figuresOUTplayer2 : g.figuresOUTplayer1); 
            
            //end game if king was the target
            if(letter == 'K'){
                b.moveFigure(movementFromTo.first, movementFromTo.second, true);
                api.showBoard();
                api.updateFigures(g);
                if(playingSide == 1){
                    api.showAlert("GAME OVER , RED WINS, PRESS ANY KEY TO END");
                }else{
                    api.showAlert("GAME OVER , BLUE WINS, PRESS ANY KEY TO END");
                }
                return;
            }     
        }
        b.moveFigure(movementFromTo.first, movementFromTo.second, true);

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
            api.updateFigures(g);
            api.showAlert("CHECK MATE, PRESS ANY KEY TO END");
            return;
        }
        swapSides();
    } 
    
    
    api.saveGame(
        b,
        g,
        "2",
        "0",
        checkDetected ? "1" : "0",
        checkMateDetected ? "1" : "0",
        stalemateDetected ? "1" : "0",
        std::to_string(playingSide) 
        );
}

