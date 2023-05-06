#pragma once

#include "../../API/Api.h"
#include "../Core/Game.h"
#include "../Core/Board.h"
#include "../Constants.h"
#include <memory>


class GameControl{
public:
    Game g;
    Board b;
    API api;
    GameControl();
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
    bool gameIsOver = false; 

    virtual void handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo) = 0;

    void handlePawnPromotion(const std::pair< Coordinates,Coordinates > & movementFromTo);
};

