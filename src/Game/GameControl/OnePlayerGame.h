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
     * @param int difficulty ... 1 = easy, 2 = mid, 3 = difficult
     */
    OnePlayerGame(int difficulty);
    void startGameLoop();
private:
    std::unique_ptr<ComputerPlayer> ptrComputer;
    int mDifficulty;
};