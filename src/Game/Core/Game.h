
#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Board.h"
#include "Coordinates.h"

class Game{
public:
    
   std::vector<std::shared_ptr<Piece>> piecesPlayer1, piecesPlayer2;
   std::list<std::shared_ptr<Piece>> piecesOUTplayer1, piecesOUTplayer2;
   std::list<std::shared_ptr<Piece>> piecesINplayer1, piecesINplayer2;
   
    void kickout(std::shared_ptr<Piece> pieceToKickout);

    void kickout(Coordinates coordinatesOfPieceToKickOut, std::list<std::shared_ptr<Piece>> & dstToMoveKickedPiece);

    void checkEnPassant(Coordinates selectedPosition, Coordinates pieceCoordinates);

    bool detectCastlingAttempt( Coordinates selectedPosition , Coordinates piecePosition);

    bool checkIfPieceWasKickedOut(Coordinates coordinates);

    bool castle(Board & b, Coordinates selectedPosition, Coordinates pieceCoordinates);

    bool checkIfPawnReachedEnd(int playingSide);

    Game();

    void clearDefault();

    void findKingsIndex();

    bool moveIsValid(Coordinates coordinatesOfPieceToMove, Coordinates selectedPosition);

    void addMoveToHistory(std::pair<Coordinates, Coordinates> fromTo, std::shared_ptr<Piece> ptrPiece);
    
    struct MoveHistory{
        Coordinates from,to;
        std::shared_ptr<Piece> ptrPiece;
    };

    const std::list<MoveHistory> & getMovesHistory();


private:
    
    int indexOfKingSide1 = 4;
    int indexOfKingSide2 = 4;
    
    const int LIMIT_HIST_MOVES = 5;
    std::list<MoveHistory> movesHistory;

    bool positionReachable(int playingSide, Coordinates positionToReach);


   
};