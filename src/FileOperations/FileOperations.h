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
#include "../Game/ConstantsGame.h"

class FileOperations{
public:

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
     * Saves game into file.
     * @param content = raw content, function will count hash and add it at the end for future control
     */
    bool saveGameToFile(std::string & content);

    /**
     * Saves game into file.
     */
    bool saveGameToFile(
        int gameType,
        int difficulty,
        int isCheck,
        int isCheckMate,
        int isStalmate,
        int plyingSide,
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