#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Rock.h"
#include "Pieces/Pawn.h"
#include "Position.h"
#include "Coordinates.h"
#include <vector>

class Board {
public:

    static const int BOARD_SIZE = 8;
    static Position playField[BOARD_SIZE][BOARD_SIZE];
    Board();

    /**
     * Puts figures from lists given as parameters to the playField[8][8]
     */
    static void setFiguresOnBoard(const std::list<std::shared_ptr<Figure>> & figuresPlayer1, const std::list<std::shared_ptr<Figure>> & figuresPlayer2);
    
    /**
     * Just collects data for connection with UI, 
     * it is not used in MinMax, it's purpose is just to collect data about figures and their
     * sides and positions, so that they can be properly displayed.
     * 
     **/
    void moveFigure(Coordinates from, Coordinates to, bool shouldIncreaseNumberOfSteps);

    /**
     * Makes castling (2 moves at once -> rock and king)
     * @return true = castling was successfull otherwise false
     */
    bool castle(Coordinates selectedPosition, Coordinates figureCoordinates);

    /**
     * @return true = other side can targen given position
     */
    bool positionReachable(int playingSide, Coordinates positionToReach);

    /**
     * Loops through playField and sets coordinates of figures (their own coordinates) to 
     * actual coordinates (the coordinates on which they are located on playField)
     * Usage: after MinMax and game state detection to rule out possible bugs
     */
    void refreshFigureCoordinates();

    /**
     * initializes playField, puts initial values to figures and sets them to default positions
     */
    void initPlayField();

private:
   
    int indexOfKing = 4;

    
    
};

