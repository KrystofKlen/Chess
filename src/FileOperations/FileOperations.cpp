#include "FileOperations.h"

bool FileOperations::saveGameToFile(
    const SaveData & saveData,
    const std::vector<PieceFileData> & piecesIn,
    const std::vector<PieceFileData> & piecesOut,
    int board[8][8],
    const std::vector<HistoryFileData> & historyMoves
){
    std::string fileContent = writingAutomata.getFileContent(
    saveData,
    piecesIn,
    piecesOut,
    board,
    historyMoves);

    std::string verifiedFile = writingAutomata.addVerification(fileContent).append(fileContent);

    std::ofstream ofs;
    ofs.open("load.game");
    if( !(ofs << verifiedFile)){
        ofs.close();
        return false;
    } 
    ofs.close();
    return true;
}

bool FileOperations::loadGameFromFile(
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
    std::ifstream ifs(fileName);
    if(ifs.fail()){
        ifs.close();
        return false;
    } 

    std::stringstream strStream;
    std::string fullFileContent,verificationContent,gameContent;

    char c;
    while(ifs.get(c)){
        strStream<<c;
    }

    fullFileContent = strStream.str();
    strStream.str("");

    readingAutomata.splitVerificationAndFile(fullFileContent,verificationContent,gameContent);
    //throw std::runtime_error(std::to_string(ACCEPT_ONLY_VERIFIED_FILES));
    if( ACCEPT_ONLY_VERIFIED_FILES ){
        int key = -1;
        readingAutomata.readVerification(verificationContent,key);
        bool verified = fileVerifier.verifyFile(gameContent,key);
        if(!verified)
            return false;
    }

    bool parsedOK = readingAutomata.readGameFromFile(
        gameContent,
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
    
    return parsedOK;
}

