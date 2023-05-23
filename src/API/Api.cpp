#include "Api.h"

API::API(){}

void API::update(Game& g){
    showBoard();
    showMovesHistory(g.getMovesHistory());
    updatePieces(g);
}

void API::handleGameEvent(const std::string &message){
    uiNcurses.setAlert(ui.ALERT_COLOR_CODE, message);
}

void API::promotePawn(Coordinates coordinatesOfPawn, Game &g, Board &b)
{
    std::shared_ptr<Piece> & ref =  Board::playField[coordinatesOfPawn.mRowIndex][coordinatesOfPawn.mColumnIndex].mPiece;
    int playingSide = ref->mSide;

    std::vector<std::pair<char,int>> kicked;
    kicked.push_back({QUEEN,playingSide});
    kicked.push_back({BISHOP,playingSide});
    kicked.push_back({KNIGHT,playingSide});
    kicked.push_back({ROCK,playingSide});

    std::shared_ptr<Piece> promotedPiece;

    char letter = uiNcurses.selectPieceToMoveBack(kicked,playingSide);
    switch (letter)
    {
    case QUEEN:
        promotedPiece = std::make_shared<Queen>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;

    case BISHOP:
        promotedPiece = std::make_shared<Bishop>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;
    
    case KNIGHT:
        promotedPiece = std::make_shared<Knight>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;
    
    case ROCK:
        promotedPiece = std::make_shared<Rock>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;
    
    default:
        break;
    }

    std::vector<std::shared_ptr<Piece>>::iterator itAllPieces;
    std::list<std::shared_ptr<Piece>>::iterator itINpieces;
    //finding piece
    if(playingSide == 1){
        for(itAllPieces = g.piecesPlayer1.begin(); *itAllPieces != ref; itAllPieces++);

        for(itINpieces = g.piecesINplayer1.begin(); *itINpieces != ref; itINpieces++);
    }   
    else{
        for(itAllPieces = g.piecesPlayer2.begin(); *itAllPieces != ref; itAllPieces++);

        for(itINpieces = g.piecesINplayer2.begin(); *itINpieces != ref; itINpieces++);
    }
    
    *itINpieces = promotedPiece;
    *itAllPieces = promotedPiece;
    ref = promotedPiece;
}

void API::closeScreen(){
    getch();
    ui.endScreen();
}

void API::endForLoadingError(){
    ui.endScreen();
    std::cout<<"ERROR : Game could not be loaded. Possible reasons:\n";
    std::cout<<" 1. File \"load.game\" doesn't exist.\n";
    std::cout<<" 2. Unknown content of the file.\n";
    std::cout<<" 3. file was modified and the data about game is not valid.\n";
}

std::pair<Coordinates,Coordinates> API::pickPosition( int sidePlaying, bool & gameIsRunning){
    std::pair< std::pair<int,int>, std::pair<int,int> > fromTo = uiNcurses.pickPosition(sidePlaying);

    if(fromTo.first.first == -1){
        gameIsRunning = false;
    }
    return 
    {
        {fromTo.first.first ,fromTo.first.second},
        {fromTo.second.first, fromTo.second.second}
    };
}

void API::updatePieces( Game & g){
    
    getInfoAboutPlayingPieces(UI::infoAboutPieces);
    getInfoAboutKickedPieces(g);
    uiNcurses.setPlayingPiecesOnScreen();
    uiNcurses.setKickedPiecesOnScreen(infoAboutKickedPieces);

}

void API::showMovesHistory(const std::list<Game::MoveHistory> & historyMoves){
    std::vector<UI::Move> uiMoves;
    for(auto move : historyMoves){
        std::string playerName = "";
        
        if(!move.ptrPiece){
            uiMoves.push_back({playerName,'x',0,0,0,0});
        }else{
            if(move.ptrPiece->mSide == 1){
                playerName = "1";
            }else{ 
                playerName = "2";
            }
            uiMoves.push_back(
            {
                playerName,
                move.ptrPiece->mLetter,
                move.from.mRowIndex,
                move.from.mColumnIndex,
                move.to.mRowIndex,
                move.to.mColumnIndex
            }
        );
        }
        
    }
    uiNcurses.showMovesHistory(uiMoves);
}

void API::showBoard(){
    //ui.printAscii();
    uiNcurses.showChessBoard();
}

void API::showAlert( const std::string & message){
    ui.setAlert(ui.ALERT_COLOR_CODE, message);
}

void API::getInfoAboutPlayingPieces(std::pair<char,int> infoAboutPieces [Board::BOARD_SIZE][Board::BOARD_SIZE]){

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(! Board::playField[i][j].mIsFree){
                infoAboutPieces[i][j] =  {
                    Board::playField[i][j].mPiece->mLetter,
                    Board::playField[i][j].mPiece->mSide
                };
            }else{
                infoAboutPieces[i][j] = { '\0', -1 };
            }
        }
    }
}

void API::getInfoAboutKickedPieces(Game & g){

    infoAboutKickedPieces.clear();

    for(auto & kickedPiece : g.piecesOUTplayer1){
        infoAboutKickedPieces.push_back(std::make_pair(kickedPiece->mLetter, kickedPiece->mSide));
    }
    for(auto & kickedPiece : g.piecesOUTplayer2){
        infoAboutKickedPieces.push_back(std::make_pair(kickedPiece->mLetter, kickedPiece->mSide));
    }
}


void API::appendInfoAboutPiece(const std::list<std::shared_ptr<Piece>> & pieces, std::stringstream & strStream){
    for(const auto & x : pieces){
            strStream <<  x->mLetter;
            strStream <<  "{" ;
            strStream <<  x.get()->mSide;
            strStream <<  ",";
            strStream <<  "{";
            strStream <<  x.get()->mCoordinates.mRowIndex;    
            strStream <<  ",";
            strStream <<  x.get()->mCoordinates.mColumnIndex;
            strStream <<  "},";
            strStream <<  x.get()->mNumOfStepsDone;
            strStream <<  ",";
            strStream <<  x.get()->mId;
            strStream <<  "}";
            strStream <<  "\n";
    }
}

void API::getInfoAboutGameToSave( const Board & b, const Game & g, std::string & info ){

    std::list<Coordinates> enPassantTrue;
    std::stringstream strStream;
    
    // save information whether position is free or not
    for(int rowIndex = 0; rowIndex<Board::BOARD_SIZE; rowIndex++){
        for(int columnIndex = 0; columnIndex<Board::BOARD_SIZE; columnIndex++){
            const Position & posRef = Board::playField[rowIndex][columnIndex];
            if(posRef.mIsFree){
                strStream <<"1";
            }else{
                strStream <<"0";
            }   
        }
        strStream <<"\n";
    }

    //info about pieces
    strStream <<"&\n";
    appendInfoAboutPiece(g.piecesINplayer1, strStream);
    strStream <<"&\n";
    appendInfoAboutPiece(g.piecesINplayer2, strStream);
    strStream <<"&\n";
    appendInfoAboutPiece(g.piecesOUTplayer1, strStream);
    strStream <<"&\n";
    appendInfoAboutPiece(g.piecesOUTplayer2, strStream);
    strStream <<"&\n";

    info.append(strStream.str());
}

void API::saveGame(
    const Board & b,
    const Game & g,
    const SaveData & saveData
     ){
        Converter conv;
        std::vector<PieceFileData> piecesIn, piecesOut;
        PieceFileData piece;
        for(auto ptrPiece : g.piecesINplayer1){         
            conv.convertPiece(ptrPiece, piece);
            piecesIn.push_back(piece);
        }
        for(auto ptrPiece : g.piecesINplayer2){
            conv.convertPiece(ptrPiece, piece);
            piecesIn.push_back(piece);
        }
        for(auto ptrPiece : g.piecesOUTplayer1){
            conv.convertPiece(ptrPiece,piece);
            piecesOut.push_back(piece);
        }
        for(auto ptrPiece : g.piecesOUTplayer2){
            conv.convertPiece(ptrPiece, piece);
            piecesOut.push_back(piece);
        }
        
        int board[8][8];
        conv.getIsFreeData(board);

        std::vector<HistoryFileData> historyMovesFileData;
        HistoryFileData historyFileData;
        auto historyMoves = g.getMovesHistory();
        for(auto move : historyMoves){
            conv.convertHistoryMove(move,historyFileData);
            historyMovesFileData.push_back(historyFileData);
        }
       
        bool saved = fo.saveGameToFile(
            saveData,
            piecesIn,
            piecesOut,
            board,
            historyMovesFileData
        );  
        if(saved)
            std::cout<<"YOUR GAME WAS SAVED.\n";
        else    
            std::cout<<"ERROR DURING WRITING TO A FILE.\n";   
}

void API::addHistoryMoves(const std::vector<HistoryFileData> & vctHistoryFileData, Game & g){
    Game::MoveHistory move;
    for(const auto & moveFileData : vctHistoryFileData){        
        conv.convertHistoryMoveFileData(moveFileData,move);
        g.addMoveToHistory(move);
    }
}

bool API::createPiecesFromFileData(
        Game & g,
        std::list<PieceFileData> &piecesIn,
        std::list<PieceFileData> &piecesOut)
        {   
            Converter conv;
            std::shared_ptr<Piece> ptr;

            for(auto piece : piecesIn){
                ptr = conv.createPieceFromFileData(piece);
                if(piece.mSide == 1){
                    g.piecesPlayer1.push_back(ptr);
                    g.piecesINplayer1.push_back(ptr);
                }else if (piece.mSide == 2){
                    g.piecesPlayer2.push_back(ptr);
                    g.piecesINplayer2.push_back(ptr);
                }else{
                    return false;
                }
            }

            for(auto piece : piecesOut){
                ptr = conv.createPieceFromFileData(piece);
                if(piece.mSide == 1){
                    g.piecesPlayer1.push_back(ptr);
                    g.piecesOUTplayer1.push_back(ptr);
                }else if (piece.mSide == 2){
                    g.piecesPlayer2.push_back(ptr);
                    g.piecesOUTplayer2.push_back(ptr);
                }else{
                    return false;
                }
            }

            return true;
        }


bool API::loadGameInfoFromFile(
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
        std::vector<HistoryFileData> & vctHistoryFileData
        ){  
    //get info from file
    bool successfullyLoaded = 
        fo.loadGameFromFile(
            fileName,
            gameType,
            difficulty,
            isCheck,
            isCheckMate,
            isStalmate,
            playingSide,
            piecesIn,
            piecesOut,
            board,
            vctHistoryFileData
            );

    if(!successfullyLoaded){
        return false;
    }

    return true;
}

int API::selectNewGameOrLoadFromFile(){
    
    std::string choice = ui.showMenu({"NEW GAME", "LOAD GAME"});
    if(choice.compare("END") == 0){
        return END_FLAG;
    }
    if(choice.compare("NEW GAME") == 0) return NEW_GAME_SELECTED;
    else return LOAD_GAME_FROM_FILE_SELECTED;
}

int API::selectOnePlayerOrTwoPlayers(){

    std::string choice = ui.showMenu({"ONE PLAYER", "TWO PLAYERS","TUTORIAL"});
    if(choice.compare("END") == 0){
        return END_FLAG;
    }
    if(choice.compare("ONE PLAYER") == 0) return ONE_PLAYER_GAME;
    else if (choice.compare("TWO PLAYERS") == 0) return TWO_PLAYERS_GAME;
    else return TUTORIAL;
}

int API::askForDifficulty(){

    std::string choice = ui.showMenu({"EASY","MID","DIFFICULT"});
    if(choice.compare("END") == 0){
        return END_FLAG;
    }
    if(choice.compare("EASY") == 0) return EASY_LEVEL;
    else if(choice.compare("MID") == 0) return MID_LEVEL;
    else return DIFFICULT_LEVEL;
}