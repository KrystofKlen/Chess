#pragma once
#include "GameControl.h"

#include "../Engine/AI/ComputerPlayer.h"
#include "../Engine/AI/EasyLevel.h"
#include "../Engine/AI/MidLevel.h"
#include "../Engine/AI/DifficultLevel.h"

class OnePlayerGame : public GameControl{
public:

    /**
     * @param int difficulty
     */
    OnePlayerGame(int difficulty,std::shared_ptr<ApiBase> apiBase);
    void startGameLoop();
private:
    std::unique_ptr<ComputerPlayer> ptrComputer;
    int mDifficulty;

    void handleKickout(const std::pair< Coordinates,Coordinates > & movementFromTo);

    void makeMoveForPC();

};