#pragma once
#include "ComputerPlayer.h"

class DifficultLevel : public ComputerPlayer{
public:
    DifficultLevel();

    /**
     * MinMax alg. player2 = pc searches minimun, user searches maximum
     * @param bool maxSearch = always false! (recursive alg.)
     * @param std::list<std::pair<int, std::pair<Coordinates, Coordinates>>> & movesRank inout parameter, first = rank of move, second = move {from, to}
     */
    int minMax (Game & g,  Board & b, bool maxSearch, int depth, std::list<std::pair<int, std::pair<Coordinates, Coordinates>>> & movesRank);
    
    /**
     * Evaluates playField at the end of minMax (when depth == 0)
     */
    int evaluetePlayField(Game& g);

    /**
     * MinMax algorythm is used to determine the best move
     * depth of minMax = 3
     * If more moves have the same (lowest evaluation), random move from these is picked.
     */
    void makeNextMove(Game & g, Board & b, bool & pcWin);

private:

    /**
     * @brief Kick out piece just for Min Max purposes
     * 
     */
    void temporarilyKickOut(std::shared_ptr<Piece> & kickedPiece, Coordinates move);

    void returnTemporarilyKickedPiece(std::shared_ptr<Piece> & kickedPiece, Coordinates to);
    
    int evaluateImportanceOfKickedPiece(std::shared_ptr<Piece> & kickedPiece);

    int evaluateMove(Game &g, Board &b, std::shared_ptr<Piece> &fig, 
    const Coordinates &move, bool maxSearch, int depth, 
    std::list<std::pair<int, std::pair<Coordinates, Coordinates>>> &movesRank);

};