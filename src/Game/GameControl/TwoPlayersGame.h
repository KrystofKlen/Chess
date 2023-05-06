#pragma once
#include "GameControl.h"
#include "GameStateController.h"

class TwoPlayersGame : public GameControl{
public:
    void startGameLoop();
private:
    void handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo);
};