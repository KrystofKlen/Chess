#pragma once
#include "../Core/Game.h"

bool kingWillNotLandIntoCheck(Game & g , Coordinates & anticipatedPosition, std::shared_ptr<Piece> king);

bool isCheckMate(Game & g, Board & b, int sidePlaying);

bool isStalmate(Game & g, Board & b, int sidePlaying);

bool kingIsInCheck(Game & g, Board & b, int sidePlaying);

bool kingWillNotLandIntoCheck( Game & g, Board & b, Coordinates & anticipatedPosition, std::shared_ptr<Piece> king );

bool kingWillNotLandIntoCheck( Game & g,  Board & b, Coordinates & anticipatedPosition, int sidePlaying );