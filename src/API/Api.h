#pragma once
#include "../config/ConstantsGame.h"
#include "../Game/Engine/Core/Board.h"
#include "../Game/Engine/Core/Game.h"
#include "../UI/UI.h"
#include "../FileOperations/FileOperations.h"
#include "Converter.h"
#include "ApiBase.h"

class API : public ApiBase{
public:
    
    API();

    void update(Game & g);

    void handleGameEvent(const std::string & message);

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

    void showMovesHistory(const std::list<Game::MoveHistory> & historyMoves);

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

    void saveGame(
    const Board & b,
    const Game & g,
    int gameType,
    int difficulty,
    int isCheck,
    int isCheckMate,
    int isStalmate, 
    int playingSide
     );

    /**
     * Converts text data into actual data types, and sets it
     */
    void convertData( Game & g, bool & isCheck, bool & isCheckMate, bool & isStalmate, int & playingSide );


    void addHistoryMoves(const std::vector<HistoryFileData> & vctHistoryFileData, Game & g);


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
        int board[8][8],
        std::vector<HistoryFileData> & vctHistoryFileData);
    
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
    Converter conv;

    std::list<std::pair<char,int>> infoAboutKickedPieces;

    /**
     * @brief Get information about the pieces that have been kicked out of the board during the game.
     * 
     * @param g The Game object to get information from.
     */
    void getInfoAboutPlayingPieces(std::pair<char,int> infoAboutPieces [Board::BOARD_SIZE][Board::BOARD_SIZE]);

    /**
     * @brief Get information about playing pieces on the board.
     * 
     * @param infoAboutPieces A 2D array of pairs representing the position and side of the playing pieces.
     *                        If a position is empty, the pair will have a null character and a side of -1.
     */
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

