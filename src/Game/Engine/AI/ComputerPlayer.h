#pragma once
#include <random>
#include <chrono> 
#include "../Core/Game.h"
#include "../Core/Board.h"



class ComputerPlayer{
public:
    virtual void makeNextMove(Game & g,  Board & b, bool & pcWin) = 0;
    void generateAllMoves(Game & g,std::vector<std::pair<Coordinates, Coordinates>> & allPossibleMoves);
    void getHighestRankMove(Game & g, std::pair<Coordinates, Coordinates> & move );
    const int PLAYING_PLAYER = 2;
    virtual ~ComputerPlayer(){};
protected:
    void kickoutByComputer(Game & g, bool & pcWon, const Coordinates & to);
};