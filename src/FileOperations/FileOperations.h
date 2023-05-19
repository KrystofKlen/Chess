#pragma once
#include <iostream>
#include <fstream> 
#include <sstream>
#include <sys/time.h>
#include <ctime>
#include <unordered_map> 
#include <cmath>
#include <vector>
#include "ReadingAutomata.h"
#include "WritingAutomata.h"
#include "../config/ConstantsGame.h"

class FileOperations{
public:
    /**
    Loads the game information from a file.
    @param fileName The name of the file to load the game information from.
    @param gameType The type of the game.
    @param difficulty The difficulty of the game.
    @param isCheck Whether the player playing is currently in check.
    @param isCheckMate Whether the player playing is currently in checkmate.
    @param isStalmate Whether the player playing is currently in stalemate.
    @param playingSide The current side playing.
    @param piecesIn The pieces on the board.
    @param piecesOut The pieces out of play.
    @param board The state of the board.
    @param vctHistoryFileData The history of moves.
    @return true if the game was successfully loaded from the file, false otherwise.
    */
    bool loadGameFromFile(
        const std::string & fileName, 
        int & gameType,
        int & difficulty,
        int & isCheck,
        int & isCheckMate,
        int & isStalmate,
        int & playingSide,
        std::list<PieceFileData> & piecesIn,
        std::list<PieceFileData> & piecesOut,
        int board[8][8],
        std::vector<HistoryFileData> & vctHistoryFileData
    );

    /**
    Saves the game information to a file.
    @param gameType The type of the game.
    @param difficulty The difficulty of the game.
    @param isCheck Whether the game is player playing is in check.
    @param isCheckMate Whether player playing is currently in checkmate.
    @param isStalmate Whether player playing is currently in stalemate.
    @param plyingSide The current side playing.
    @param piecesIn The pieces on the board.
    @param piecesOut The pieces out of play.
    @param board The state of the board.
    @param historyMoves The history of moves.
    @return true if the game was successfully saved to a file, false otherwise.
    */
    bool saveGameToFile(
        const SaveData & saveData,
        const std::vector<PieceFileData> & piecesIn,
        const std::vector<PieceFileData> & piecesOut,
        int board[8][8],
        const std::vector<HistoryFileData> & historyMoves
    );
private: 
    FileVerifier fileVerifier;
    ReadingAutomata readingAutomata;
    WritingAutomata writingAutomata;
};