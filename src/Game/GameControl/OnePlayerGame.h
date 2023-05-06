#pragma once
#include "GameControl.h"
#include "GameStateController.h"

#include "../AI/ComputerPlayer.h"
#include "../AI/EasyLevel.h"
#include "../AI/MidLevel.h"
#include "../AI/DifficultLevel.h"

class OnePlayerGame : public GameControl{
public:

    /**
     * @param int difficulty
     */
    OnePlayerGame(int difficulty);
    void startGameLoop();
private:
    std::unique_ptr<ComputerPlayer> ptrComputer;
    int mDifficulty;
};