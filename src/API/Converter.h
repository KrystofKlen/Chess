#pragma once
#include <memory>
#include <sstream>
#include "../Game/Engine/Core/Pieces/King.h"
#include "../Game/Engine/Core/Pieces/Queen.h"
#include "../Game/Engine/Core/Pieces/Bishop.h"
#include "../Game/Engine/Core/Pieces/Knight.h"
#include "../Game/Engine/Core/Pieces/Rock.h"
#include "../Game/Engine/Core/Pieces/Pawn.h"
#include "../Game/Engine/Core/Game.h"
#include "../FileOperations/FileOperations.h"
#include<iostream>

class Converter{
public:
/**
 * @brief Creates a new piece from the given chunk of data.
 *
 * @param figureData The string containing the data for the piece.
 * @return A shared pointer to the created piece.
 */
std::shared_ptr<Piece> createPieceFromChunk(const std::string & figureData);

/**
 * @brief Creates a new piece from the given file data.
 *
 * @param pieceFileData The struct containing the data for the piece.
 * @return A shared pointer to the created piece.
 */
std::shared_ptr<Piece> createPieceFromFileData(const PieceFileData & pieceFileData);

/**
 * @brief Sets the isFree data of the Board from a string.
 *
 * @param strIsFree The string containing the isFree data for the Board.
 */
void setIsFreeData(const std::string & strIsFree);

/**
 * @brief Sets the isFree data of the Board from a 2D integer array.
 *
 * @param board The 2D integer array containing the isFree data for the Board.
 */
void setIsFreeData(const int board[8][8]);

/**
 * @brief Gets the isFree data of the Board and stores it in a 2D integer array.
 *
 * @param board The 2D integer array to store the isFree data of the Board.
 */
void getIsFreeData(int board[8][8]);

/**
 * @brief Converts a Piece object to a PieceFileData struct.
 *
 * @param from The shared pointer to the Piece object to convert.
 * @param to The PieceFileData struct to store the converted data.
 */
void convertPiece(std::shared_ptr<Piece> from, PieceFileData & to);

/**
 * @brief Converts a MoveHistory object to a HistoryFileData struct.
 *
 * @param from The MoveHistory object to convert.
 * @param to The HistoryFileData struct to store the converted data.
 */
void convertHistoryMove(const Game::MoveHistory & from, HistoryFileData & to);

/**
 * @brief Converts a HistoryFileData struct to a MoveHistory object.
 *
 * @param from The HistoryFileData struct to convert.
 * @param to The MoveHistory object to store the converted data.
 */
void convertHistoryMoveFileData(const HistoryFileData & from, Game::MoveHistory & to);


};

