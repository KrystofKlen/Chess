#pragma once
#include "../../API/Api.h"
#include "../Engine/Core/Game.h"
#include "../Engine/Core/Board.h"
#include <memory>
#include "../../API/ApiBase.h"


class GameControl{
public:
    Game g;
    Board b;
    std::shared_ptr<ApiBase> apiBase;
    GameControl(std::shared_ptr<ApiBase> apiBase);
    virtual ~GameControl(){};

    /**
     * Sets game state after loading from a content from a file was successfully loaded.
     */
    void setGameState(bool isCheck, bool isStalmate, bool isCheckMate, int playingSide);


    void setGameHistoryMoves(const std::vector<Game::MoveHistory> & historyMoves){
        for(const auto & move : historyMoves){
            g.addMoveToHistory(move);
        }
    }

    /**
     * To be implemented ... 
     * usages: 1 player game (against PC), 2 players game
     */
    virtual void startGameLoop() = 0;

protected:
    void swapSides();
    int playingSide;
    bool checkDetected;
    bool checkMateDetected;
    bool stalemateDetected;    
    bool gameRunning = true;

    virtual void handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo) = 0;

    void handlePawnPromotion(const std::pair< Coordinates,Coordinates > & movementFromTo);

    bool isCheckMate( int sidePlaying);

    bool isStalmate( int sidePlaying);

    bool kingIsInCheck( int sidePlaying);

    bool kingWillNotLandIntoCheck( Coordinates & anticipatedPosition, std::shared_ptr<Piece> king );

    bool checkIfKingStillInCheck(Coordinates &anticipatedPosition, std::shared_ptr<Piece> pieceMoving,std::shared_ptr<Piece> king);

    bool kingWillNotLandIntoCheck(Coordinates & anticipatedPosition, int sidePlaying );

    void checkGameState();

    void handleChangedState();

    bool validateMove(std::pair< Coordinates,Coordinates > movementFromTo);

};

