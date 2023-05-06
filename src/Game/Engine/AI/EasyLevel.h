#pragma once
#include "ComputerPlayer.h"

class EasyLevel : public ComputerPlayer{
public:

    /**
     * Makes just random moves
     * @param bool & pcWin .. inout parameter .. if pc wins -> pcWin = true
     */
    void makeNextMove( Game & g, Board & b, bool & pcWin);
    EasyLevel();
};
