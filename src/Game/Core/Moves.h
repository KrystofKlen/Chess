#pragma once
#include "Figures/King.h"
#include "Figures/Queen.h"
#include "Figures/Bishop.h"
#include "Figures/Knight.h"
#include "Figures/Rock.h"
#include "Figures/Pawn.h" 
#include "Board.h"
#include <list> 
   
enum CastlingSide {SHORTER_SIDE, LONGER_SIDE};

/**
 * Example:
 * . . . .
 * . Q . .
 * . . B .
 * . . . .
 * 
 * B can not move to the top left corner, because Q is blocking the way,
 * this function can detect whether position is blocked
 * @return true = loop adding positions to go should be left, because position is blocked, false = OK, position can be added
 */
bool breakBecausePositionBlocked(int x, int y, int side, std::list<Coordinates> & possiblePositions);

//Various function to generate moves

void addMovesVertical(std::list<Coordinates> & possiblePositions, const Figure & figure);
void addMovesHorizontal(std::list<Coordinates> & possiblePositions, const Figure & figure);
void addMoves1Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure);
void addMoves2Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure);
void addMoves3Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure);
void addMoves4Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure);
void addMovesKnight(std::list<Coordinates> & possiblePositions,  const Figure & figure);

//side 1 = side playing "downwards" and having figures up
void addQuadrantsForPawnSide1(std::list<Coordinates> & possiblePositions, const Figure & figure);

//side 1 = side playing "upwards" and having figures down
void addQuadrantsForPawnSide2(std::list<Coordinates> & possiblePositions, const Figure & figure);

/**
 * adds move possibilities for en passant, function returns emmidiately if
 * given figure is not Pawn 
 * @param std::list<Coordinates> & possiblePositions - possible positions of figure
 * @param const Figure & figure ... pawn
 */
void addEnPassantForPawn(std::list<Coordinates> & possiblePositions, const Figure & figure);

/**
 * Adds position for king to castle
 * Moves added only if castling conditions are met!
 * @param std::list<Coordinates> & possiblePositions - possible positions of king
 * @param const Figure & figure ... pking
 */
void addCastlingPositionsForKing(std::list<Coordinates > & castlingPositions, const Figure & figure);

/**
 * Differs from "addQuadrantsForPawnSide1" !!!, this function will automatically 
 * add quadrants-moves for pawn.
 * Usage: detection whether king stepped into check intentionally
 */
void addPawnPossibleKickoutsSide1(std::list<Coordinates> & possiblePositions, const Figure & pawn);

/**
 * Differs from "addQuadrantsForPawnSide2" !!!, this function will automatically 
 * add quadrants-moves for pawn.
 * Usage: detection whether king stepped into check intentionally
 */
void addPawnPossibleKickoutsSide2(std::list<Coordinates> & possiblePositions, const Figure & pawn);