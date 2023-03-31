#pragma once

#include "../Game/Core/Board.h"
#include "../Game/Core/Game.h"
#include "../UI/UI.h"
#include "../FileOperations/FileOperations.h"
#include "Converter.h"


class API{
public:
    static const int END_FLAG = -1;
    
    API();

    /**
     * Closes screen at the end of application.
     */
    void closeScreen();

    /**
     * Application is closed, possible reasons for failed loading of file written to console
     */
    void endForLoadingError();

    /**
     * Updates pieces in and out of game (including their colors, positions etc.)
     */
    void updatePieces(Game & g);

    /**
     * shows plain chess board
     */
    void showBoard();

    /**
     * Displays message underneeth the chess board
     * @param const std::string & message = message to display
     */
    void showAlert(const std::string & message);

    /**
     * User will pick a piece and position, 
     * if piece of his own side taken, and position selected, its is returned.
     * NO CONTROL THAT USER MADE A MOVE CONSISTENT WITH CHESS RULES!!!
     * @param  bool & gameIsRunning ... if user presses 'q' = quit and save gameIsRunning = false, otherwise gameIsRunning = true
     * @return std::pair<Coordinates,Coordinates> .. first = position with piece, second = position to go
     */
    std::pair<Coordinates,Coordinates> pickPosition(int sidePlaying, bool & gameIsRunning);
    void appendInfoAboutPiece(const std::list<std::shared_ptr<Piece>> & pieces, std::stringstream & strStream );
    void getInfoAboutGameToSave( const Board & b, const Game & g, std::string & info);
    void promotePawn(Coordinates coordinatesOfPawn, Game & g, Board & b);

    /**
     * gameType 1 = one player against PC, 2 = 2palyersGame
     */
    void saveGame( const Board & b, const Game & g, const std::string & gameType,
        const std::string & difficulty,
        const  std::string & isCheck,const std::string & isCheckMate, const std::string & isStalmate, const std::string & playingSide );

    /**
     * Converts text data into actual data types, and sets it
     */
    void convertData( Game & g, bool & isCheck, bool & isCheckMate, bool & isStalmate, int & playingSide );


    bool createPiecesFromFileData(
        Game & g,
        std::list<PieceFileData> & piecesIn,
        std::list<PieceFileData> & piecesOut);

    /**
     * @brief loads necessary game info from file
     * 
     * @param fileName 
     * @param gameType 
     * @param difficulty 
     * @param isCheck 
     * @param isCheckMate 
     * @param isStalmate 
     * @param playingSide 
     * @return true 
     * @return false 
     */
    bool loadGameInfoFromFile(
        const std::string & fileName, 
        int & gameType,
        int & difficulty,
        int & isCheck,
        int & isCheckMate,
        int & isStalmate,
        int & playingSide,
        std::list<PieceFileData> & piecesIn,
        std::list<PieceFileData> & piecesOut,
        int board[8][8]);
    
    /**
     * displays menu with following options: new game, load from file
     * @return 1 = new game, 2 = load from file
     */
    int selectNewGameOrLoadFromFile();

     /**
     * displays menu with following options: one player, two players
     * @return 1 = one player, 2 = two players
     */
    int selectOnePlayerOrTwoPlayers();

    /**
     * 1 = easy, 2 = mid, 3 = difficult
     */
    int askForDifficulty();
    
private:

    UI ui;
    FileOperations fo;

    std::list<std::pair<char,int>> infoAboutKickedPieces;

    void getInfoAboutPlayingPieces(std::pair<char,int> infoAboutPieces [Board::BOARD_SIZE][Board::BOARD_SIZE]);

    void getInfoAboutKickedPieces(Game & g);

    std::string strPlayingSide;
    std::string strIsCheck;
    std::string strIsCheckMate;
    std::string strIsStalmate;
    std::string strIsFree;
    std::string strPiecesInPlayer1;
    std::string strPiecesInPlayer2;
    std::string strPiecesOUTplayer1;
    std::string strPiecesOUTplayer2;

};

