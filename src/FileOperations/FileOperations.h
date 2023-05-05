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
     * @brief DEPRECATED
     * 
     *
     * Reads from file and stores info into given parameters.
     * @return true = file was succesfully read and hash matches, otherwise false
     */
    bool loadGameFromFile2(const std::string & fileName, 
    std::string & gameType,
    std::string & difficulty,
    std::string & isCheck,
    std::string & isCheckMate,
    std::string & isStalmate,
    std::string & playingSide,
    std::string & positionIsFreeData,
    std::string & in1,
    std::string & in2,
    std::string & out1,
    std::string & out2);

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
    int getHash(std::string & info, long saveTime);
    bool controlHash(std::string & info);

    /**
     * Reads text until it reaches specified delimiter.
     * @param std::stringstream & strStream ... this stream will be cleared when hitting delimiter!
     */
    void readNextChunk(
        std::stringstream & strStream, 
        char delimiter,
        const std::string & fileContent, 
        std::string::const_iterator & it);
    

};