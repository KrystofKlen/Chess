#include "Application.h"

void Application::launch(){

    //check condition for game
    if(!checkTerminalRequirements()){
        std::cout<<"YOUR TERMINAL DOES NOT FULFIL THE MINIMUM SIZE (50 ROWS, 43 COLUMNS)"<<std::endl;
        return;
    }

    std::unique_ptr<GameControl> chessGame;

    int choiceFromMenu = api.selectNewGameOrLoadFromFile();
    if(choiceFromMenu == API::END_FLAG){
        return;
    }

    if(choiceFromMenu == 2){
        // load game from a file
        int gameType, difficulty, isCheck, isCheckMate, isStalmate, playingSide;
        std::list<PieceFileData>  piecesIn;
        std::list<PieceFileData>  piecesOut;
        int board[8][8];
        
        bool succesfullyLoaded = api.loadGameInfoFromFile(
            PATH_TO_LOAD,
            gameType,
            difficulty,
            isCheck,
            isCheckMate,
            isStalmate,
            playingSide,
            piecesIn,
            piecesOut,
            board);
        if(!succesfullyLoaded){
            std::string s;
            for(auto p : piecesIn){
                s.append(std::to_string(p.mId) + ", ");
            }
            api.endForLoadingError(s);    
            return;
        }
        if(gameType == ONE_PLAYER_GAME){
            chessGame = std::make_unique<OnePlayerGame>(difficulty);
        }else{
            chessGame = std::make_unique<TwoPlayersGame>();
        }

        chessGame->g.clearDefault();
        
        api.createPiecesFromFileData(chessGame->g, piecesIn, piecesOut);
        //api.convertData(chessGame->g, isCheck, isCheckMate, isStalmate, playingSide);

        chessGame->setGameState(isCheck, isStalmate, isCheckMate, playingSide);

    }else{
        //starting a new game
        choiceFromMenu = api.selectOnePlayerOrTwoPlayers();
        if(choiceFromMenu == API::END_FLAG){
            return;
        }
        if(choiceFromMenu == 1){
            //game against computer
            int difficulty = api.askForDifficulty();
            chessGame = std::make_unique<OnePlayerGame>(difficulty);
        }else{
            //2 players on one computer
            chessGame = std::make_unique<TwoPlayersGame>();
        }
    }
    chessGame->g.findKingsIndex();
    chessGame->startGameLoop();
    api.closeScreen();

}

bool Application::checkTerminalRequirements(){

    //getting terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return
    w.ws_row >= minTerminalRows &&
    w.ws_col >= minTerminalColumns;

}