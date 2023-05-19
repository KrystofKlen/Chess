#pragma once
#include "../UI/UI.h"
#include "../Game/Engine/Core/Game.h"
#include "SaveData.h"
class ApiBase{
    public:
        virtual void update(Game & g) = 0;
        virtual void promotePawn(Coordinates coordinatesOfPawn,  Game & g, Board & b) = 0;
        virtual std::pair<Coordinates,Coordinates> pickPosition( int sidePlaying, bool & gameIsRunning ) = 0;
        virtual void handleGameEvent(const std::string & message) = 0;
        virtual void saveGame( const Board & b,const Game & g, const SaveData & saveData) = 0;
        virtual int selectNewGameOrLoadFromFile() = 0;
        virtual int selectOnePlayerOrTwoPlayers() = 0;
        virtual int askForDifficulty() = 0;
    protected: 
        UI uiNcurses;
};