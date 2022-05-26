
#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Board.h"
#include "Coordinates.h"

class Game{
public:
    
   std::vector<std::shared_ptr<Figure>> figuresPlayer1, figuresPlayer2;
   std::list<std::shared_ptr<Figure>> figuresOUTplayer1, figuresOUTplayer2;
   std::list<std::shared_ptr<Figure>> figuresINplayer1, figuresINplayer2;

    void kickout(std::shared_ptr<Figure> figureToKickout);

    void kickout(Coordinates coordinatesOfFigureToKickOut, std::list<std::shared_ptr<Figure>> & dstToMoveKickedFigure);

    void checkEnPassant(Coordinates selectedPosition, Coordinates figureCoordinates);

    bool detectCastlingAttempt( Coordinates selectedPosition , Coordinates figurePosition);

    bool checkIfFigureWasKickedOut(Coordinates coordinates);

    bool castle(Board & b, Coordinates selectedPosition, Coordinates figureCoordinates);

    bool checkIfPawnReachedEnd(int playingSide);

    Game();

    void clearDefault();

    void findKingsIndex();

    bool moveIsValid(Coordinates coordinatesOfFigureToMove, Coordinates selectedPosition);

private:
    
    int indexOfKingSide1 = 4;
    int indexOfKingSide2 = 4;

    bool positionReachable(int playingSide, Coordinates positionToReach);


   
};