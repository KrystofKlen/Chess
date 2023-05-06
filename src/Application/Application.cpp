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

    if(choiceFromMenu == API::LOAD_GAME_FROM_FILE_SELECTED){
        bool successfullyLoaded = loadFromFile(chessGame);
        if(!successfullyLoaded) return;
    }else{
        startNewGame(choiceFromMenu,chessGame);
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

bool Application::loadFromFile(std::unique_ptr<GameControl> &chessGame){
    // load game from a file
    int gameType, difficulty, isCheck, isCheckMate, isStalmate, playingSide;
    std::list<PieceFileData>  piecesIn;
    std::list<PieceFileData>  piecesOut;
    std::vector<HistoryFileData> vctHistoryFileData;
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
        board,
        vctHistoryFileData);
    if(!succesfullyLoaded){
        api.endForLoadingError();    
        return false;
    }
    if(gameType == API::ONE_PLAYER_GAME){
        chessGame = std::make_unique<OnePlayerGame>(difficulty);
    }else if (gameType == API::TWO_PLAYERS_GAME){
        chessGame = std::make_unique<TwoPlayersGame>();
    }else {
        std::cout<<"GAME DIFFICULTY HAS WRONG NUMBER, 0 = ONE PLAYER GAME, 2 = TWO PLAYERS GAME\n"<<std::endl;
        return false;
    }

    chessGame->g.clearDefault();
    
    api.createPiecesFromFileData(chessGame->g, piecesIn, piecesOut);
    //api.convertData(chessGame->g, isCheck, isCheckMate, isStalmate, playingSide);

    chessGame->setGameState(isCheck, isStalmate, isCheckMate, playingSide);
    api.addHistoryMoves(vctHistoryFileData,chessGame->g);
    return true;
}

void Application::startNewGame(int choiceFromMenu, std::unique_ptr<GameControl> &chessGame){
    //starting a new game
    choiceFromMenu = api.selectOnePlayerOrTwoPlayers();
    if(choiceFromMenu == API::END_FLAG){
        return;
    }
    if(choiceFromMenu == API::ONE_PLAYER_GAME){
        //game against computer
        int difficulty = api.askForDifficulty();
        chessGame = std::make_unique<OnePlayerGame>(difficulty);
    }else{
        //2 players on one computer
        chessGame = std::make_unique<TwoPlayersGame>();
    }
}