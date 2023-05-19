#pragma once
#include "GameControl.h"
#include "GameStateController.h"

class TwoPlayersGame : public GameControl{
public:
    void startGameLoop();
    TwoPlayersGame(std::shared_ptr<ApiBase> apiBase);
private:
    void handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo);
};