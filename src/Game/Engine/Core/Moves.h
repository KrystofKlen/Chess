#pragma once
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Rock.h"
#include "Pieces/Pawn.h" 
#include "Board.h"
#include "../../../config/ConstantsEngine.h"
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
void addMovesVerticalAndHorizontal(std::list<Coordinates> & possiblePositions, const Piece & piece, int rowChange, int colChange);
void addMovesVertical(std::list<Coordinates> & possiblePositions, const Piece & piece);
void addMovesHorizontal(std::list<Coordinates> & possiblePositions, const Piece & piece);
void addMovesInDirection(std::list<Coordinates> &possiblePositions, const Piece &piece, int rowOffset, int colOffset);
void addMoves1Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece);
void addMoves2Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece);
void addMoves3Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece);
void addMoves4Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece);
void addMovesKnight(std::list<Coordinates> & possiblePositions,  const Piece & piece);
bool canEnPassantCapture(const Piece& piece, int dx, int dy);

//side 1 = side playing "downwards" and having pieces up
void addQuadrantsForPawnSide1(std::list<Coordinates> & possiblePositions, const Piece & piece);

//side 1 = side playing "upwards" and having pieces down
void addQuadrantsForPawnSide2(std::list<Coordinates> & possiblePositions, const Piece & piece);

/**
 * adds move possibilities for en passant, function returns emmidiately if
 * given piece is not Pawn 
 * @param std::list<Coordinates> & possiblePositions - possible positions of piece
 * @param const Piece & piece ... pawn
 */
void addEnPassantForPawn(std::list<Coordinates> & possiblePositions, const Piece & piece);

/**
 * Adds position for king to castle
 * Moves added only if castling conditions are met!
 * @param std::list<Coordinates> & possiblePositions - possible positions of king
 * @param const Piece & piece ... pking
 */
void addCastlingPositionsForKing(std::list<Coordinates > & castlingPositions, const Piece & piece);

/**
 * Differs from "addQuadrantsForPawnSide1" !!!, this function will automatically 
 * add quadrants-moves for pawn.
 * Usage: detection whether king stepped into check intentionally
 */
void addPawnPossibleKickoutsSide1(std::list<Coordinates> & possiblePositions, const Piece & pawn);

/**
 * Differs from "addQuadrantsForPawnSide2" !!!, this function will automatically 
 * add quadrants-moves for pawn.
 * Usage: detection whether king stepped into check intentionally
 */
void addPawnPossibleKickoutsSide2(std::list<Coordinates> & possiblePositions, const Piece & pawn);