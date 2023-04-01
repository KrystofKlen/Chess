#pragma once
#include <memory>
#include <sstream>
#include "../Game/Core/Pieces/King.h"
#include "../Game/Core/Pieces/Queen.h"
#include "../Game/Core/Pieces/Bishop.h"
#include "../Game/Core/Pieces/Knight.h"
#include "../Game/Core/Pieces/Rock.h"
#include "../Game/Core/Pieces/Pawn.h"
#include "../FileOperations/FileOperations.h"
#include<iostream>

class Converter{
public:

    /**
     * Reand until the next delimiter.
     */
    void readNextChunk(std::stringstream & strStream, char delimiter, const std::string & fileContent, std::string::const_iterator & it);

    /**
     * Breaks up chunk into strings that can represent enitities.
     */
    void breakUpChunks(const std::string & strChunk, std::list<std::string> & chunks);

    /**
     * Creates actual objects from chunks
     */
    std::shared_ptr<Piece> createPieceFromChunk(const std::string & figureData);


    std::shared_ptr<Piece> createPieceFromFileData(const PieceFileData & pieceFileData);

    /**
     * Sets mIsFree attribute into playField
     */
    void setIsFreeData(const std::string & strIsFree);

    void setIsFreeData(const int board[8][8]);

    void getIsFreeData(int board[8][8]);

    void convertPiece(std::shared_ptr<Piece> from, PieceFileData & to);

};

