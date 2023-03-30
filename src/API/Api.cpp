#include "Api.h"

API::API(){}

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
    std::pair< std::pair<int,int>, std::pair<int,int> > fromTo = ui.pickPosition(sidePlaying);

    if(fromTo.first.first == -1){
        gameIsRunning = false;
    }
    return 
    {
        {fromTo.first.first ,fromTo.first.second},
        {fromTo.second.first, fromTo.second.second}
    };
}


void API::promotePawn(Coordinates coordinatesOfPawn,  Game & g, Board & b){

    std::shared_ptr<Piece> & ref =  Board::playField[coordinatesOfPawn.mRowIndex][coordinatesOfPawn.mColumnIndex].mPiece;
    int playingSide = ref->mSide;

    std::vector<std::pair<char,int>> kicked;
    kicked.push_back({'Q',playingSide});
    kicked.push_back({'B',playingSide});
    kicked.push_back({'H',playingSide});
    kicked.push_back({'R',playingSide});

    std::shared_ptr<Piece> promotedPiece;

    char letter = ui.selectPieceToMoveBack(kicked,playingSide);
    switch (letter)
    {
    case 'Q':
        promotedPiece = std::make_shared<Queen>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;

    case 'B':
        promotedPiece = std::make_shared<Bishop>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;
    
    case 'H':
        promotedPiece = std::make_shared<Knight>(playingSide, coordinatesOfPawn, 0, ref->mId);
        break;
    
    case 'R':
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


void API::updatePieces( Game & g){
    
    getInfoAboutPlayingPieces(UI::infoAboutPieces);
    getInfoAboutKickedPieces(g);
    ui.setPlayingPiecesOnScreen();
    ui.setKickedPiecesOnScreen(infoAboutKickedPieces);
}

void API::showBoard(){
    ui.printAscii();
    ui.showChessBoard();
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



void API::saveGame( const Board & b, const Game & g,
 const std::string & gameType, const std::string & difficulty, const std::string & isCheck,const std::string & isCheckMate,const std::string & isStalmate, const std::string & playingSide){
    std::string content;
    content.append(gameType);
    content.append("\n&\n");
    content.append(difficulty);
    content.append("\n&\n");
    content.append(isCheck);
    content.append("\n&\n");
    content.append(isCheckMate);
    content.append("\n&\n");
    content.append(isStalmate);
    content.append("\n&\n");
    content.append(playingSide);
    content.append("\n&\n");
    getInfoAboutGameToSave( b, g, content);
    bool saved = fo.saveGameToFile(content);
    if(saved)
        std::cout<<"YOUR GAME WAS SAVED.\n";
    else    
        std::cout<<"ERROR DURING WRITING TO A FILE.\n"; 

}

void API::convertData(Game & g, bool & isCheck, bool & isCheckMate, bool & isStalmate, int & playingSide){

    // set is check
    if(strIsCheck.compare("1") == 0){
        isCheck = true;
    }else{
        isCheck = false;
    }

    // set is check mate
    if(strIsCheckMate.compare("1") == 0){
        isCheckMate = true;
    }else{
        isCheckMate = false;
    }

    // set is Stalmate
    if(strIsStalmate.compare("1") == 0){
        isStalmate = true;
    }else{
        isStalmate = false;
    }

    //set playingSide
    playingSide = std::stoi(strPlayingSide);

    //create pieces
    Converter conv;
    conv.setIsFreeData(strIsFree);
   
    std::shared_ptr<Piece> ptr;
        
    std::list<std::string> chunksPieces;
    conv.breakUpChunks(strPiecesInPlayer1, chunksPieces);
    for(const std::string & chunk : chunksPieces){
        ptr = conv.createPieceFromChunk(chunk);
        if(ptr == nullptr){
            endForLoadingError();
        }
        g.piecesPlayer1.emplace_back(ptr);
        g.piecesINplayer1.emplace_back(ptr);
    }
    chunksPieces.clear();

    conv.breakUpChunks(strPiecesInPlayer2, chunksPieces);
    for(const std::string & chunk : chunksPieces){
        ptr = conv.createPieceFromChunk(chunk);
        if(ptr == nullptr){
            endForLoadingError();
        }
        g.piecesPlayer2.push_back(ptr);
        g.piecesINplayer2.push_back(ptr);
    }
    chunksPieces.clear();

    conv.breakUpChunks(strPiecesOUTplayer1, chunksPieces);
    for(const std::string & chunk : chunksPieces){
        ptr = conv.createPieceFromChunk(chunk);
        if(ptr == nullptr){
            endForLoadingError();
        }
        g.piecesPlayer1.push_back(ptr);
        g.piecesOUTplayer1.push_back(ptr);
    }
    chunksPieces.clear();

    conv.breakUpChunks(strPiecesOUTplayer2, chunksPieces);
    for(const std::string & chunk : chunksPieces){
        ptr = conv.createPieceFromChunk(chunk);
        if(ptr == nullptr){
            endForLoadingError();
        }
        g.piecesPlayer2.push_back(ptr);
        g.piecesOUTplayer2.push_back(ptr);
    }
    chunksPieces.clear();
}

bool API::loadGameInfoFromFile(const std::string fileName, std::string & gameType,
std::string & difficulty){  
    //get info from file
    bool successfullyLoaded = 
    fo.loadGameFromFile(fileName, gameType, difficulty, strIsCheck, strIsCheckMate, strIsStalmate, strPlayingSide, strIsFree, strPiecesInPlayer1, strPiecesInPlayer2,
        strPiecesOUTplayer1, strPiecesOUTplayer2);

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
    if(choice.compare("NEW GAME") == 0) return 1;
    else return 2;
}

int API::selectOnePlayerOrTwoPlayers(){

    std::string choice = ui.showMenu({"ONE PLAYER", "TWO PLAYERS"});
    if(choice.compare("END") == 0){
        return END_FLAG;
    }
    if(choice.compare("ONE PLAYER") == 0) return 1;
    else return 2;
}

int API::askForDifficulty(){

    std::string choice = ui.showMenu({"EASY","MID","DIFFICULT"});
    if(choice.compare("END") == 0){
        return END_FLAG;
    }
    if(choice.compare("EASY") == 0) return 1;
    else if(choice.compare("MID") == 0) return 2;
    else return 3;
}