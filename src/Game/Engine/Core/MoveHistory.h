#pragma once
#include "Coordinates.h"
#include <memory>
#include "Piece.h"
struct MoveHistory{
    Coordinates from,to;
    std::shared_ptr<Piece> ptrPiece;
};