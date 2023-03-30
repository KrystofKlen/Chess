#pragma once
#include<ncurses.h>
#include<string>
#include<numeric>
#include<list>
#include <vector>
#include<iterator>

class UI{

public:
    
    static std::pair<char,int> infoAboutPieces[8][8];
    struct Field{
        WINDOW* mPtrWindow;
        int mColorPairCode;
        chtype charRepresentingPiece;
        int mSide;
    };
    void endScreen();
    void setSelected(int playingSide, chtype charRepresentigPiece);
    void drawDownWindow(WINDOW** win,  int* winDownSize, int lines, const char* headline);
    void showChessBoard();
    std::pair< std::pair<int,int>, std::pair<int,int> > pickPosition(int sidePlaying );
    void setPlayingPiecesOnScreen();
    void setKickedPiecesOnScreen(const std::list<std::pair<char,int>> & infoAboutKickedPieces);
    void setAlert(int COLOR_PAIR_CODE, const std::string & message);
    std::string showMenu(std::list<std::string> options);
    void setKickedPiecesOnScreen(const std::list<std::pair<char,int>> & infoAboutKickedPieces, WINDOW* winKickedPieces);
    char selectPieceToMoveBack(const std::vector<std::pair<char,int>> & infoAboutKickedPieces, int playingSide);
    void printAscii();
    void printManualMenu();
    void printManualGame();
    void initWindows();
    void freeWindows();

    static const int BACKGROUND_PAIR_CODE = 1;
    static const int BLACK_PAIR_CODE = 2;
    static const int WHITE_PAIR_CODE = 3;
    static const int SELECTED_FIELD_CODE = 4;
    static const int PLAYER_1_COLOR_CODE = 5;
    static const int PLAYER_2_COLOR_CODE = 6;
    static const int ALERT_COLOR_CODE = 7;
private:
    const int winSize = 3;
    Field board[8][8];
    WINDOW* pWinAlert;
    WINDOW* pWinDown;
    WINDOW* pWinKickedPieces;
    WINDOW* inputWin;
};