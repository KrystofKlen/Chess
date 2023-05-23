#include "UI.h"
#define COLOR_BACKGROUND 0
#define COLOR_OTHER_FIELD 145
#define SELECTED_FIELD_COLOR 118
#include <signal.h>
#include <cstdlib>
#include <iostream>
#include <csignal>

std::pair<char,int> UI::infoAboutPieces[8][8];

void UI::endScreen(){
    keypad(stdscr, false);
    endwin();
}

void UI::printChessBoardDiscription(){
    int x = CHESS_BOARD_START_X + winSize - 1;
    for(char c = 'A'; c<='H'; c++ ){
        mvaddch(CHESS_BOARD_START_Y-winSize/2 - 1,x+=2*winSize,c);
    }
    int y = CHESS_BOARD_START_Y-winSize + winSize/2;
    for(char c = '0'; c<='7';c++){
        mvaddch( y+=winSize,CHESS_BOARD_START_X+winSize, c);
    }
    refresh();
}

void UI::showChessBoard(){
    initscr();
    cbreak();
    noecho();

    curs_set(0);

    initWindows();

    printAscii();
    printManualGame();
    printChessBoardDiscription();

    start_color();

    init_pair(BACKGROUND_PAIR_CODE,COLOR_OTHER_FIELD, COLOR_BACKGROUND);
    init_pair(YELLOW_PAIR_CODE,COLOR_YELLOW, COLOR_YELLOW);
    init_pair(WHITE_PAIR_CODE,COLOR_OTHER_FIELD, COLOR_OTHER_FIELD);
    init_pair(SELECTED_FIELD_CODE,COLOR_BLACK, SELECTED_FIELD_COLOR);
    init_pair(PLAYER_1_COLOR_CODE,COLOR_WHITE, COLOR_RED);
    init_pair(PLAYER_2_COLOR_CODE,COLOR_WHITE, COLOR_BLUE);
    init_pair(ALERT_COLOR_CODE,COLOR_WHITE, COLOR_GREEN);

    bkgd(COLOR_PAIR(BACKGROUND_PAIR_CODE));
    refresh();

    bool prevBlack = true;
    for(int rowIndex = 0; rowIndex < 8; rowIndex++){

        int columnWindowFrom = CHESS_BOARD_START_X;

        for(int columnIndex = 0; columnIndex < 8; columnIndex++, prevBlack = !prevBlack){
                board[rowIndex][columnIndex].mPtrWindow =
                    newwin(winSize, winSize*2, CHESS_BOARD_START_Y + rowIndex*winSize, columnWindowFrom += (winSize*2) );
                            
            if(prevBlack){
                board[rowIndex][columnIndex].mColorPairCode = 2;
                wbkgd(board[rowIndex][columnIndex].mPtrWindow, COLOR_PAIR(YELLOW_PAIR_CODE));
            }else{
                board[rowIndex][columnIndex].mColorPairCode = 3;
                wbkgd(board[rowIndex][columnIndex].mPtrWindow, COLOR_PAIR(WHITE_PAIR_CODE));
            }

            wrefresh(board[rowIndex][columnIndex].mPtrWindow);       
        }
        prevBlack = !prevBlack;
    }
}

std::pair< std::pair<int,int>, std::pair<int,int> > UI::pickPosition(int sidePlaying){
    
    keypad(stdscr, true);
    int keyPressed = 0;
    int rowSelected = 0;
    int colSelected = 0;
    Field selectedField = board[rowSelected][colSelected];
    std::pair<int,int> selectedCoordinatesWithPieceToMove;
    std::list<std::pair<int,int>> possibleMoves;
    Field fieldToRepaint = selectedField;
    wbkgd(selectedField.mPtrWindow,COLOR_PAIR(4));
    wrefresh(selectedField.mPtrWindow);

    // runs intil player selects his piece and makes a move (by pressing enter)
    // whether a move is legal or not is handled elsewhere
    while(true){
        keyPressed = getch();
        switch (keyPressed){
        case KEY_UP:
            if(rowSelected == 0){
                break;
            }
            fieldToRepaint = selectedField;
            selectedField = board[--rowSelected][colSelected];
            break;
        case KEY_DOWN:
            if(rowSelected == 7){
                break;
            }
            fieldToRepaint = selectedField;
            selectedField = board[++rowSelected][colSelected];
            break;
        case KEY_LEFT:
            if(colSelected == 0){
                break;
            }
            fieldToRepaint = selectedField;
            selectedField = board[rowSelected][--colSelected];
            break;
        case KEY_RIGHT:
            if(colSelected == 7){
                break;
            }
            fieldToRepaint = selectedField;
            selectedField = board[rowSelected][++colSelected];
            break;
        case ' ':
            attron(A_BOLD);
            if(selectedField.mSide != sidePlaying){   
                //field with no piece, or piece of other player selected  
                setAlert( YELLOW_PAIR_CODE,"WRONG CHOICE");
                break;
            }
            setSelected( sidePlaying,selectedField.charRepresentingPiece);
            selectedCoordinatesWithPieceToMove = {rowSelected,colSelected};
            break;
        case 'h':
            if(board[selectedCoordinatesWithPieceToMove.first][selectedCoordinatesWithPieceToMove.second].mSide != sidePlaying){   
                //field with no piece, or piece of other player selected  
                printPieceManual(' ');
                break;
            }
            printPieceManual(selectedField.charRepresentingPiece);

        case 'm':
            if(board[selectedCoordinatesWithPieceToMove.first][selectedCoordinatesWithPieceToMove.second].mSide != sidePlaying){   
                //field with no piece, or piece of other player selected  
                break;
            }
            wbkgd(selectedField.mPtrWindow, COLOR_PAIR(selectedField.mColorPairCode));
            wrefresh(selectedField.mPtrWindow); 
            keypad(stdscr, false);
            freeWindows();
            return {
                selectedCoordinatesWithPieceToMove,
                {rowSelected,colSelected}
            };
        case 'q':
            endScreen();
            keypad(stdscr, false);
            freeWindows();
            endwin(); 
            return{{-1,-1}, {-1,-1}};

        case KEY_RESIZE:
            endScreen();
            keypad(stdscr, false);
            freeWindows();
            endwin(); 
            return{{-1,-1}, {-1,-1}};
        case ('^' + 'C') :
            endScreen();
            keypad(stdscr, false);
            freeWindows();
            endwin(); 
            return{{-1,-1}, {-1,-1}};

                
        default:
            continue;
        }
        wbkgd(fieldToRepaint.mPtrWindow,COLOR_PAIR(fieldToRepaint.mColorPairCode));
        wbkgd(selectedField.mPtrWindow,COLOR_PAIR(4));
        
        wrefresh(fieldToRepaint.mPtrWindow);  
        wrefresh(selectedField.mPtrWindow);       
    }
}

void UI::setPlayingPiecesOnScreen(){

    for(int rowIndex = 0; rowIndex < 8; rowIndex++){
        for(int columnIndex = 0; columnIndex < 8; columnIndex++){
            
            if (infoAboutPieces[rowIndex][columnIndex].first == '\0'){
                board[rowIndex][columnIndex].mSide = -1;   
                continue;
            }
                
            if(infoAboutPieces[rowIndex][columnIndex].second == 1){
                board[rowIndex][columnIndex].charRepresentingPiece = 
                infoAboutPieces[rowIndex][columnIndex].first | COLOR_PAIR(PLAYER_1_COLOR_CODE);
                board[rowIndex][columnIndex].mSide = 1;
            }else{
                board[rowIndex][columnIndex].charRepresentingPiece = 
                infoAboutPieces[rowIndex][columnIndex].first | COLOR_PAIR(PLAYER_2_COLOR_CODE);
                board[rowIndex][columnIndex].mSide = 2;
            }    
            
            mvwaddch(board[rowIndex][columnIndex].mPtrWindow, 
            winSize/2 , winSize-1,
            board[rowIndex][columnIndex].charRepresentingPiece
            );
        
            wbkgd(board[rowIndex][columnIndex].mPtrWindow,COLOR_PAIR(board[rowIndex][columnIndex].mColorPairCode)); 

            wrefresh(board[rowIndex][columnIndex].mPtrWindow);  
        }   
    }  
}

void UI::setKickedPiecesOnScreen(const std::list<std::pair<char,int>> & infoAboutKickedPieces){    
    WINDOW* winKickedPieces = newwin(KICKED_FIGURES_LINES,KICKED_FIGURES_COLLS, STATS_Y,STATS_WIN_X);   
    refresh();
    box(winKickedPieces,0,0);
    mvwprintw(winKickedPieces, 0, KICKED_FIGURES_COLLS/2 - 7, "KICKED FIGURES");
    wrefresh(winKickedPieces);

    int column = 1;
    for(auto x : infoAboutKickedPieces){
        if(x.second == 1){
            mvwaddch(winKickedPieces,1,column++, x.first | COLOR_PAIR(PLAYER_1_COLOR_CODE));
        }else{
            mvwaddch(winKickedPieces,1,column++, x.first | COLOR_PAIR(PLAYER_2_COLOR_CODE));
        }
        wrefresh(winKickedPieces);
    }
}

void UI::setAlert(int COLOR_PAIR_CODE, const std::string & message){
    pWinAlert = NULL;
    int windowAlertSize;
    drawDownWindow(&pWinAlert,&windowAlertSize,3,"");
    mvwprintw(pWinAlert, 1, windowAlertSize/2 - message.size()/2, message.c_str());
    wrefresh(pWinAlert); 
}

void UI::showMovesHistory(const std::vector<Move> & moves){
    int ASCII = 65;
    winMovesHistory = newwin(HISTORY_LINES,HISTORY_COLLS, STATS_Y + KICKED_FIGURES_LINES + 1, HISTORY_X); 
    box(winMovesHistory,0,0);
    int line = 2;
    for(auto move : moves){
        std::string player = "PLAYER:";
        player.append(move.mPlayer);

        std::string piece = "PIECE:";

        std::string from = "FROM:";
        char cFrom = move.fromCol+ASCII;
        from += cFrom;
        from.append(std::to_string(move.fromRow));

        std::string to = "TO:";
        char cTo = move.toCol+ASCII;
        to += cTo;
        to.append(std::to_string(move.toRow));

        mvwprintw(winMovesHistory,line,5,player.c_str() );
        mvwprintw(winMovesHistory,line,16,piece.c_str() );
        if(move.mPlayer.compare("1") ==0){
            mvwaddch(winMovesHistory,line,23, move.mLetter | COLOR_PAIR(PLAYER_1_COLOR_CODE));
        }else{
            mvwaddch(winMovesHistory,line,23, move.mLetter | COLOR_PAIR(PLAYER_2_COLOR_CODE));
        }
        mvwprintw(winMovesHistory,line,26,from.c_str() );
        mvwprintw(winMovesHistory,line,36,to.c_str());
        line++;
        wrefresh(winMovesHistory);
        attroff(COLOR_PAIR(PLAYER_1_COLOR_CODE));
    }
    wrefresh(winMovesHistory);
    
}

void UI::drawDownWindow(WINDOW** win, int* winDownSize, int lines, const char* headline){    
    //creating window
    *winDownSize = winSize*2*8;
    int columnWindowFrom = 0;
    int rowWindowFrom = 3 + 8*winSize + 6;

    *win = newwin(lines,*winDownSize, STATS_Y + KICKED_FIGURES_LINES + HISTORY_LINES + 2 , STATS_WIN_X);   
    refresh();
    box(*win,0,0);
    mvwprintw(*win, 0, (*winDownSize)/2 - 7, headline);
    wrefresh(*win);
}

void UI::setSelected(int playingSide, chtype charRepresentigPiece){
    pWinDown = NULL;
    int winDownSize;
    int lines = 3;
    drawDownWindow(&pWinDown, &winDownSize,  lines, "");
    mvwprintw(pWinDown,1, 2 , "FIGURE SELECTED: ");
    mvwaddch(pWinDown, 1, 19, charRepresentigPiece);
    
    if(playingSide == 1){
        mvwprintw(pWinDown,1, winDownSize -  16, "NOW PLAY: RED");
    }else{
        mvwprintw(pWinDown,1, winDownSize -  16 , "NOW PLAY: BLUE");
    }
    
    wrefresh(pWinDown);
}

std::string UI::showMenu(std::list<std::string> options){

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    //printAscii();
    //printManualMenu();
    
    int winLines = options.size() + 2;
    int winColumns = 30;
    inputWin = newwin(winLines, winColumns, 7,  0);
    box(inputWin,0,0);
    start_color();
    init_pair(BACKGROUND_PAIR_CODE,COLOR_WHITE, COLOR_BACKGROUND);
    init_pair(BACKGROUND_PAIR_CODE,COLOR_OTHER_FIELD, COLOR_BACKGROUND);
    bkgd(COLOR_PAIR(BACKGROUND_PAIR_CODE));
    refresh();

    keypad(inputWin, true);
    int choice = 0;
    std::list<std::string> :: const_iterator highlightedPosition = options.begin();

    while(1){
        int line = 1;
        for(std::list<std::string> :: const_iterator it = options.begin();
        it != options.end(); it++, line++){
            if(it == highlightedPosition){
                wattron(inputWin, A_REVERSE);
            }
            mvwprintw(inputWin,line, winColumns/2 - (*it).size()/2 ,(*it).c_str());
            wattroff(inputWin, A_REVERSE);
        }

        choice = wgetch(inputWin);
        switch (choice){
        case KEY_UP: 
                    highlightedPosition == options.begin() 
                    ? highlightedPosition = --options.end() : highlightedPosition--;
                    break;
        case KEY_DOWN: 
                    highlightedPosition == --options.end() 
                    ? highlightedPosition = options.begin() : highlightedPosition++;
                    break;
        case KEY_RESIZE:
                    
                    keypad(stdscr, false);
                    delwin(inputWin);
                    endScreen();
                    endwin(); 
                    return "END";
        case 's':
                delwin(inputWin);
                return *highlightedPosition;
        default:
            continue;
        }
        
        if(choice == 10)
            break;
    }
    return "";
}

char UI::selectPieceToMoveBack(const std::vector<std::pair<char,int>> & playersKickedPieces, int playingSide){

    pWinKickedPieces = NULL;
    //creating window
    int winKickedPiecesSize = winSize*2*8;
    int columnWindowFrom = 0;
    int rowWindowFrom = 3 + 8*winSize + 6;
    pWinKickedPieces = newwin(3,winKickedPiecesSize,rowWindowFrom,columnWindowFrom);   
    refresh();
    box(pWinKickedPieces,0,0);
    mvwprintw(pWinKickedPieces, 0, winKickedPiecesSize/2 - 7, "SELECT FIGURE TO SWAP");
    wrefresh(pWinKickedPieces);

    int column = 1;
    int selectedColumn = 1;
    int size = playersKickedPieces.size();
    int index = 0;
    

    keypad(pWinKickedPieces, true);
    
    while (true){
        int column = 1;
        for(auto x : playersKickedPieces){
            if(column == selectedColumn){
                mvwaddch(pWinKickedPieces,1, column++,  x.first | COLOR_PAIR(SELECTED_FIELD_CODE));
            }else if(x.second == 1){
                mvwaddch(pWinKickedPieces,1, column++,   x.first | COLOR_PAIR(PLAYER_1_COLOR_CODE));
            }else{
                mvwaddch(pWinKickedPieces,1, column++,   x.first | COLOR_PAIR(PLAYER_2_COLOR_CODE));
            }
        }
        int choice = wgetch(pWinKickedPieces);
        switch (choice){
        case KEY_LEFT:
            if(index != 0){
                index--;
                selectedColumn--;
            }  
            break;

        case KEY_RIGHT:
            if(index != size - 1){
                index++;
                selectedColumn++;
            }
            break;

        case 's':
            return playersKickedPieces[index].first;

        default:
            break;
        }
    } 
}

void UI::printAscii(){
     int rowFrom = 3 + 8*winSize + 6 + 3;
    mvwprintw
    (stdscr,rowFrom,0,"  ####  #    # ######  ####   ####  \n #    # #    # #      #      #      \n #      ###### #####   ####   #### \n #      #    # #           #      # \n #    # #    # #      #    # #    # \n  ####  #    # ######  ####   ####  \n");
    refresh();   
}

void UI::printManualMenu(){
    int rowFrom = 6+5+1;
    
    mvprintw( rowFrom++, 0, "- MOVE WITH ARROWS");
    mvprintw( rowFrom++, 0, "- CTRL+C / RESIZE TERMINAL = QUIT");
    mvprintw( rowFrom++, 0, "- s = SELECT");
    refresh();
}

void UI::printManualGame(){
    int rowFrom = 3 + 8*winSize + 6 + 3; 
    mvprintw( rowFrom++, 50, "- MOVE WITH ARROWS");
    mvprintw( rowFrom++, 50, "- q / RESIZE TERMINAL = QUIT AND SAVE");
    mvprintw( rowFrom++, 50, "- m = MOVE");
    mvprintw( rowFrom++, 50, "- h = PIECE MANUEL (PIECE MUST BE SELECTED)");
    mvprintw( rowFrom++, 50, "- space = SELECT");
    mvprintw( rowFrom++, 50, "- CTRL+C = QUIT WITHOUT SAVING");
    refresh();
}

void UI::freeWindows(){
    for(int rowIndex = 0; rowIndex < 8; rowIndex++){
        for(int columnIndex = 0; columnIndex <8; columnIndex++){
            delwin(board[rowIndex][columnIndex].mPtrWindow);
        }
    }
    delwin(pWinAlert);
    delwin(pWinKickedPieces);
    delwin(pWinDown);
    delwin(pWinChessDiscription);
    delwin(winMovesHistory);
}

void UI::printPieceManual(char selected){
    switch (selected)
    {
    case KING:
        printPieceInfo("King: The King is the most important piece in chess. Its primary objective is to avoid being captured by the opponent.\n The King can move one square in any direction—horizontally, vertically, or diagonally.\n\n\n                                                                       "); 
        break;
    
    case QUEEN:
        printPieceInfo("Queen: The Queen is the most powerful piece in chess.\n It combines the movements of a Rook and a Bishop.\n The Queen can move in any direction—horizontally, vertically, or diagonally—across any number of squares.\n\n                                                                 ");
        break;

    case ROCK:
        printPieceInfo("Rook: The Rook is a powerful piece that moves horizontally or vertically across the board.\n It can move any number of squares in a straight line, as long as there are no pieces blocking its path. \n\n                                                                                  ");
        break;
    
    case BISHOP:
        printPieceInfo("Bishop: The Bishop is a piece that moves diagonally across the board.\n It can move any number of squares in a diagonal line, as long as there are no pieces blocking its path.\n Each player has two Bishops, one on a light square and one on a dark square.   \n\n                      ");
        break;
    case KNIGHT:
        printPieceInfo("Knight: The Knight is a unique piece that moves in an L shape.\n It can move two squares in one direction (horizontally or vertically) and then one square perpendicular to that direction.\n The Knight is the only piece that can jump over other pieces. \n\n                           ");
        break;

    case PAWN:
    printPieceInfo("Pawn: Pawns are the smallest and most numerous pieces on the board.\n They are positioned in a row in front of the other pieces.\n Pawns move forward one square at a time, but they capture diagonally.\n On their first move, Pawns have the option to move forward two squares.           ");
        break;
    
    default:
        printPieceInfo("\n\n\n\n\n\n");
        break;
    }
}

void UI::printPieceInfo(const char* msg){
    mvwprintw
        (stdscr,30,0,msg);
        refresh(); 
}

void UI::initWindows(){
    for(int rowIndex = 0; rowIndex < 8; rowIndex++){
        for(int columnIndex = 0; columnIndex <8; columnIndex++){
            board[rowIndex][columnIndex].mPtrWindow = NULL;
        }
    }
}
