#pragma once
#include "ComputerPlayer.h"

class MidLevel : public ComputerPlayer{
public:
    MidLevel();

    /**
     * Makes such move, that figure with highest rank is kicked out.
     * It no figure can be kicked out, random move is selected.
     * @param bool & pcWin .. inout parameter .. if pc wins -> pcWin = true
     */
    void makeNextMove(Game & g, Board & b, bool & pcWin);
    
};