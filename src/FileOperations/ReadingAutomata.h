#include <iostream>
#include <sstream>
#include <memory>
#include <list>
#include "PieceFileData.h"

class ReadingAutomata{
public:

    /**
     * @brief Reads info from file, where game is saved. Stores game parameters.
     * @param fileContent: content of file which should be read
     * @return true all parameters read
     * @return false not all necessary parameters provided
     */
     bool readGameFromFile(
        const std::string & fileContent, 
        int & gameType,
        int & difficulty,
        int & isCheck,
        int & isCheckMate,
        int & isStalmate,
        int & playingSide,
        std::list<PieceFileData> & piecesIn,
        std::list<PieceFileData> & piecesOut,
        int board[8][8]);
private:

    /**
     * @brief Reads comment section
     * 
     * @param iss  
     * @return true : comment correctly written
     * @return false : wrong comment syntax
     */
    bool readComment(std::istringstream & iss);

    /**
     * @brief Reads (skips) variable name including = token
     * 
     * @param iss 
     * @return true : var syntax correct
     * @return false : var syntax not correct
     */
    bool readVariable(std::istringstream & iss);

    /**
     * @brief Reads number from iss and saves into num
     * 
     * @param iss 
     * @param num 
     * @return true succcess
     * @return false : number not successfully read
     */
    bool readNumber(std::istringstream & iss, int & num);

    /**
     * @brief Reads char from iss and saves into c
     * 
     * @param iss 
     * @param c 
     * @return true succcess
     * @return false : char not successfully read
     */
    bool readChar(std::istringstream & iss, char & c);
    

    /**
     * @brief Reads specific token from iss
     * 
     * @param iss 
     * @param token token to be checked / read
     * @return true : token successfully read
     * @return false : something went wrong / expected token not present
     */
    bool readToken(std::istringstream & iss, char token);
    

    /**
     * @brief Reads chess piece from iss
     *  Expected syntax:
     *  {
     *      PIECE = char;
     *      SIDE = int; 
     *      COORDINATES = {1,2};
     *      NUM_OF_STEPS = int;
     *      ID = int;
     * }
     * 
     * @param iss 
     * @param pieceSymbol 
     * @param side 
     * @param rowIndex 
     * @param columnIndex 
     * @param numOfSteps 
     * @param id 
     * @return true : read and stored into parameters
     * @return false : something went wrong / wrong syntax
     */
    bool readChessPiece(
        std::istringstream & iss, 
        char & pieceSymbol,
        int & side,
        int & rowIndex,
        int & columnIndex,
        int & numOfSteps,
        int & id
        );
    

    /**
     * @brief Reads section free positions
     * Expected syntax:
     * {
        LINE1 = 0 0 0 0 1 0 1 0;
        LINE2 = 0 0 0 0 1 0 1 0;
        LINE3 = 0 0 0 0 1 0 1 0;
        LINE4 = 0 0 0 0 1 0 1 0;
        LINE5 = 0 0 0 0 1 0 1 0;
        LINE6 = 0 0 0 0 1 0 1 0;
        LINE7 = 0 0 0 0 1 0 1 0;
        LINE8 = 0 0 0 0 1 0 1 0;
        }
     * 
     * @param iss 
     * @param board 
     * @return true 
     * @return false 
     */
    bool readFreePositions(std::istringstream & iss, int board[8][8] );
    
};

