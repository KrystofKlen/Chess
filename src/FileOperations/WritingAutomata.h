#pragma once
#include <string>
#include <vector>
#include <regex>
#include "PieceFileData.h"
#include <iostream>

class WritingAutomata{
public:

std::string getFileContent(
        int gameType,
        int difficulty,
        int isCheck,
        int isCheckMate,
        int isStalmate,
        int plyingSide,
        const std::vector<PieceFileData> & piecesIn,
        const std::vector<PieceFileData> & piecesOut,
        int board[8][8]
    );

private:

    std::string getFileTemplate(
        const std::vector<PieceFileData> & piecesIn,
        const std::vector<PieceFileData> & piecesOut
        );

    std::string getFreePositions(int board[8][8]);

    void setParamsPiece(
        const PieceFileData & piece,
        std::vector<std::string> & params
    );

    void setParamsGame(
        int gameType,
        int difficulty,
        int isCheck,
        int isCheckMate,
        int isStalmate,
        int plyingSide,
        std::vector<std::string> & params
        );



    std::string replace_nth_hashtags(std::string str, std::vector<std::string> params);

    std::string replaceHashesWithNumbers(const std::string& input, const std::vector<std::string>& vct );

    std::string replace_hashtags(std::string str, std::string replacement);


    const std::string GAME_FILE_SAVING_TEMPLATE = 
    "GAME_TYPE=#;\n"
    "DIFFICULTY=#;\n"
    "IS_CHECK=#;\n"
    "IS_CHECK_MATE=#;\n"
    "IS_STALMATE=#;\n"
    "PLAYING_SIDE=#;\n";

    const std::string COMPOSED_BRACKET_TEMPLATE = 
    "{\n#\n};\n";

    const std::string PIECES_FILE_SAVING_TEMPLATE = 
    "{\nPIECE=#;\nSIDE=#;\nCOORDINATES={#,#};\nNUM_OF_STEPS=#;\nID=#;\n}";

    const std::string FREE_POSITIONS_TEMPLATE = 
    "{\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "LINEx= # # # # # # # # ;\n"
    "};";

};
