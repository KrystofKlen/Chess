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
     * Updates figures in and out of game (including their colors, positions etc.)
     */
    void updateFigures(Game & g);

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
     * User will pick a figure and position, 
     * if figure of his own side taken, and position selected, its is returned.
     * NO CONTROL THAT USER MADE A MOVE CONSISTENT WITH CHESS RULES!!!
     * @param  bool & gameIsRunning ... if user presses 'q' = quit and save gameIsRunning = false, otherwise gameIsRunning = true
     * @return std::pair<Coordinates,Coordinates> .. first = position with figure, second = position to go
     */
    std::pair<Coordinates,Coordinates> pickPosition(int sidePlaying, bool & gameIsRunning);
    void appendInfoAboutFigure(const std::list<std::shared_ptr<Figure>> & figures, std::stringstream & strStream );
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

    /**
     * loads game info from file
     * @param const std::string fileName 
     * @param std::string & gameType ... inout parameter ... "1\n" = 1 player, "2\n" = 2 players
     * @param std::string & difficulty ... inout parameter
     */
    bool loadGameInfoFromFile ( const std::string fileName, std::string & gameType,
     std::string & difficulty );
    
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

    std::list<std::pair<char,int>> infoAboutKickedFigures;

    void getInfoAboutPlayingFigures(std::pair<char,int> infoAboutFigures [Board::BOARD_SIZE][Board::BOARD_SIZE]);

    void getInfoAboutKickedFigures(Game & g);

    std::string strPlayingSide;
    std::string strIsCheck;
    std::string strIsCheckMate;
    std::string strIsStalmate;
    std::string strIsFree;
    std::string strFiguresInPlayer1;
    std::string strFiguresInPlayer2;
    std::string strFiguresOUTplayer1;
    std::string strFiguresOUTplayer2;

};

