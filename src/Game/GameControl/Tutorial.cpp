#include "Tutorial.h"

Tutorial::Tutorial(std::shared_ptr<ApiBase> apiBase):GameControl(apiBase){
    ptrComputer = std::make_unique<EasyLevel>();
}

void Tutorial::startGameLoop(){
    
    Board::setPiecesOnBoard(g.piecesINplayer1, g.piecesINplayer2);
    
    while(gameRunning){
        b.refreshPieceCoordinates();
        //refresh UI
        apiBase->update(g);
        sendHelpMessage();

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
            b.movePiece(movementFromTo.first, movementFromTo.second, true);
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
        {
        TUTORIAL,
        EASY_LEVEL,
        checkDetected ? 1:0,
        checkMateDetected ? 1:0,
        stalemateDetected ? 1:0,
        playingSide
        }
    );
}

void Tutorial::handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo){
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

void Tutorial::makeMoveForPC(){
    bool pcWin = false;
    ptrComputer->makeNextMove(g, b, pcWin);

    if(pcWin){
        apiBase->update(g);
        apiBase->handleGameEvent("GAME OVER , RED WINS, PRESS ANY KEY TO END");
        gameRunning = false;
    }
}

void Tutorial::sendHelpMessage(){
    std::set<char> possibleKickoutsPlayer1,  possibleKickoutsPlayer2;
    std::list<Coordinates> possibleMovesPlayer1,possibleMovesPlayer2;

    for(auto & piece : g.piecesINplayer1){
        piece->getPossibleMovePositions(possibleMovesPlayer1);
    }

    for(auto & piece : g.piecesINplayer2){
        piece->getPossibleMovePositions(possibleMovesPlayer2);
    }

    findPossibleKickouts(possibleMovesPlayer1,possibleKickoutsPlayer1,1);
    findPossibleKickouts(possibleMovesPlayer2,possibleKickoutsPlayer2,2);

    std::stringstream ss;
    createMessage(ss,possibleKickoutsPlayer1,possibleKickoutsPlayer2);
    apiBase->handleGameEvent(ss.str());
}

void Tutorial::findPossibleKickouts(const std::list<Coordinates> & possibleMovesPlayer, std::set<char> &possibleKickoutsPlayer, int side){
    for(auto targettable : possibleMovesPlayer){
        const Position & posRef = Board::playField[targettable.mRowIndex][targettable.mColumnIndex];
        if(!posRef.mIsFree && posRef.mPiece->mSide != side){
            possibleKickoutsPlayer.insert(posRef.mPiece->mLetter);
        }
    }
}

void Tutorial::createMessage(std::stringstream &ss, const std::set<char> &possibleKickoutsPlayer1, const std::set<char> &possibleKickoutsPlayer2){
    ss << "Kick: ";

    for (auto it = possibleKickoutsPlayer1.begin(); it != possibleKickoutsPlayer1.end(); ++it) {
        ss << *it;
        if (std::next(it) != possibleKickoutsPlayer1.end()) {
            ss << ",";
        }
    }
    ss<<" ";

    ss<< "In danger: ";
    for (auto it = possibleKickoutsPlayer2.begin(); it != possibleKickoutsPlayer2.end(); ++it) {
        ss << *it;
        if (std::next(it) != possibleKickoutsPlayer2.end()) {
            ss << ",";
        }
    }
}
