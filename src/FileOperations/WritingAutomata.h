#include <string>
#include "PieceFileData.h"
class WritingAutomata{
public:
    // std::string getFileContent(
    //     int gameType,
    //     int difficulty,
    //     int isCheck,
    //     int isCheckMate,
    //     int isStalmate,
    //     int plyingSide,


    // ){

    // }

private:
    const std::string FILE_SAVING_TEMPLATE = 
    "GAME_TYPE=#;\n"
    "DIFFICULTY=#;\n"
    "IS_CHECK=#;\n"
    "IS_CHECK_MATE=#;\n"
    "IS_STALMATE=#;\n"
    "PLAYING_SIDE=#;\n"
    "PIECES=\n"
    "{\n"
    "{VAR1=#;VAR=#;COORD={#,#};ST=#;ID=#;}\n"
    "{VAR1=#;VAR=#;COORD={#,#};ST=#;ID=#;}\n"
    "};\n"
    "PIECES_OUT=\n"
    "{\n"
    "{VAR1 = #; VAR = #; COORD = {#,#}; ST = #; ID = #;}\n"
    "{VAR1 = #; VAR = #; COORD = {#,#}; ST = #; ID = #;}\n"
    "{VAR1 = #; VAR = #; COORD = {#,#}; ST = #; ID = #;}\n"
    "};\n";

};