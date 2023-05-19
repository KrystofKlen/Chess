#pragma once
#include <string>
#include <vector>
#include <regex>
#include "PieceFileData.h"
#include "HistoryFileData.h"
#include <iostream>
#include "FileVerifier.h"
#include "../API/SaveData.h"

class WritingAutomata{
public:

std::string getFileContent(
        const SaveData & saveData,
        const std::vector<PieceFileData> & piecesIn,
        const std::vector<PieceFileData> & piecesOut,
        int board[8][8],
        const std::vector<HistoryFileData> & historyMoves
    );

std::string addVerification(std::string & fileContent);

private:

    std::string getFileTemplate(
        const std::vector<PieceFileData> & piecesIn,
        const std::vector<PieceFileData> & piecesOut,
        const std::vector<HistoryFileData> & historyMoves
        );

    std::string getFreePositions(int board[8][8]);

    void setParamsHistory(
        const HistoryFileData & historyMove,
        std::vector<std::string> & params
    );

    void setParamsPiece(
        const PieceFileData & piece,
        std::vector<std::string> & params
    );

    void setParamsGame(
        const SaveData & saveData,
        std::vector<std::string> & params
        );



    std::string replace_nth_hashtags(std::string str, std::vector<std::string> params);

    std::string replaceHashesWithNumbers(const std::string& input, const std::vector<std::string>& vct );

    std::string replace_hashtags(std::string str, std::string replacement);

    FileVerifier fileVerifier;

    const std::string VERIFICATION_TEMPLATE = "VERIFICATION=#;\n";

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

    const std::string HISTORY_MOVE_TEMPLATE =
    "{\nPIECE=#;\nSIDE=#;\nCOORDINATES_FROM={#,#};\nCOORDINATED_TO={#,#};\n}";

};
