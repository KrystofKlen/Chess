#include <iostream>
#include <sstream>
#include "../Core/Piece.h"
#include <memory>

class ReadingAutomata{
public:
    /**
     * @brief Reads info from file, where game is saved. Stores game parameters.
     * @param fileContent: content of file which should be read
     * @return true all parameters read
     * @return false not all necessary parameters provided
     */
     bool readGameFromFile(const std::string & fileContent){
        int gameType, difficulty, isCheck,isCheckMate,isStalmate,playingSide;
        std::istringstream iss (fileContent);
        

        readComment(iss);
        if( ! readVariable(iss) || ! readNumber(iss,gameType) || ! readToken(iss,';') ){
            return false;
        }
      
        readComment(iss);
        if( ! readVariable(iss) || ! readNumber(iss,difficulty) || ! readToken(iss,';') ){
            return false;
        }
        readComment(iss);
        if( ! readVariable(iss) || ! readNumber(iss,isCheck) || ! readToken(iss,';') ){
            return false;
        }
        readComment(iss);
        if( ! readVariable(iss) || ! readNumber(iss, isCheckMate) || ! readToken(iss,';') ){
            return false;
        }
        readComment(iss);
        if( ! readVariable(iss) || ! readNumber(iss,isStalmate) || ! readToken(iss,';') ){
            return false;
        }
        readComment(iss);
        if( ! readVariable(iss) || ! readNumber(iss,playingSide) || ! readToken(iss,';') ){
            return false;
        }

        //if( ! readVariable(iss) ) return false;
        //while(  )

        std::cout << 
        gameType <<
        difficulty <<
        isCheck<<
        isCheckMate<<
        isStalmate<<
        playingSide

        <<std::endl;

        return true;
    }
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
    bool readVariable(std::istringstream & iss){
        char c;
        while(iss >> c){
            if(c == '=')return true;
        }
        return false;
    }

    /**
     * @brief Reads number from iss and saves into num
     * 
     * @param iss 
     * @param num 
     * @return true succcess
     * @return false : number not successfully read
     */
    bool readNumber(std::istringstream & iss, int & num){
        if (iss >> num) return true;
        return false;
    }

    /**
     * @brief Reads char from iss and saves into c
     * 
     * @param iss 
     * @param c 
     * @return true succcess
     * @return false : char not successfully read
     */
    bool readChar(std::istringstream & iss, char & c){
        if (iss >> c) return true;
        return false;
    }

    /**
     * @brief Reads specific token from iss
     * 
     * @param iss 
     * @param token token to be checked / read
     * @return true : token successfully read
     * @return false : something went wrong / expected token not present
     */
    bool readToken(std::istringstream & iss, char token){
        char c;
        if (iss >> c && token == c) return true;
        return false;
    }

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
        )
    {
        char c1,c2;

        // Read openning bracket
        if( !readToken(iss,'{') ){
            return false;
        }

        // Read chess piece indicator
        if ( ! readVariable(iss) || ! readChar(iss, pieceSymbol) || ! readToken(iss,';') ) return false;
  
        // Read side
        if ( ! readVariable(iss) || ! readNumber(iss, side) || ! readToken(iss,';') ) return false;
    
        // Read Coordinates
        if ( ! readVariable(iss) || ! readToken(iss, '{')  ) return false;

        // Row Index
        if ( ! readNumber(iss, rowIndex) || ! readToken(iss,',') ) return false;
        // column Index
        if ( ! readNumber(iss, columnIndex) ) return false;

        if ( ! readToken(iss, '}')  || ! readToken(iss, ';') ) return false;
         
        // Read number of steps
        if( ! readVariable(iss) || ! readNumber(iss, numOfSteps) || ! readToken(iss,';') ) return false;

        // Read ID
        if( ! readVariable(iss) || ! readNumber(iss, id) || ! readToken(iss,';') ) return false;
        
        // Read closing bracket
        if( !readToken(iss,'}') ){
            return false;
        }
         
        return true;
    }

    /**
     * @brief Reads section free positions
     * Expected syntax:
     * 
     * 
     * @param iss 
     * @param board 
     * @return true 
     * @return false 
     */
    bool readFreePositions(std::istringstream & iss, int board[8][8] ){

        if( !readToken(iss,'{') ){
            return false;
        }
        
        for(int rowIndex = 0; rowIndex<8; rowIndex++){

            if( ! readVariable(iss) )return false;
            for(int colIndex = 0; colIndex<8; colIndex++){
                if ( ! readNumber(iss, board[rowIndex][colIndex]) ) return false;
            }
            
            if(!readToken(iss,';') ){
                return false;
            }
        }
        if( !readToken(iss,'}') ){
                return false;
            }
        return true;
    }

    
};

