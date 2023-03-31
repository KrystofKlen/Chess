#include "FileOperations.h"

bool FileOperations::saveGameToFile(std::string & content){
    
    time_t timeSave = time(0);
    std::string dayTime = ctime(&timeSave); 

    // removing newline char
    dayTime.pop_back();

    for(std::string::iterator itstr = dayTime.begin(); itstr != dayTime.end(); itstr++){
        if(*itstr == ' ' || *itstr == ':'){
            *itstr = '_';
        }
    }
    dayTime.append(".game");

    int hash = getHash(content, timeSave);
    content.append("$");
    content.append(std::to_string(timeSave));
    content.append("#");
    content.append(std::to_string(hash));
    content.append("*");

    std::ofstream ofs;
    ofs.open(dayTime);
    if( !(ofs << content)) return false;
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
    std::list<ReadingAutomata::PieceFileData> & piecesIn,
    std::list<ReadingAutomata::PieceFileData> & piecesOut
){
    std::ifstream ifs(fileName);
    if(ifs.fail()) return false;

    std::stringstream strStream;
    std::string fileContent;

    char c;
    while(ifs.get(c)){
        strStream<<c;
    }
    if(ifs.fail()) return false;

    fileContent = strStream.str();
    strStream.str("");

    ReadingAutomata readingAutomata;
    bool parsedOK = readingAutomata.readGameFromFile(
        fileContent,
        gameType,
        difficulty,
        isCheck,
        isCheckMate,
        isStalmate,
        playingSide,
        piecesIn,
        piecesOut
    );
    
    return parsedOK;
}

bool FileOperations::loadGameFromFile2(
 const std::string & fileName,
 std::string & gameType,
 std::string & difficulty,
 std::string & isCheck,
 std::string & isCheckMate,
 std::string & isStalmate,
 std::string & playingSide,
 std::string & positionIsFreeData,
 std::string & in1,
 std::string & in2,
 std::string & out1,
 std::string & out2 ){
    std::ifstream ifs(fileName);
    if(ifs.fail()) return false;

    //check if file exists and if it is not damaged
    std::stringstream strStream;
    std::string fileContent;
    std::string strTimeSave;
    std::string strHash;

    char c;
    bool delimFound = false;
    while(ifs.get(c) && !delimFound){
        if (c == '$'){
            delimFound = true;
            break;
        } 
        strStream<<c;
    }
    if(ifs.fail() || !delimFound) return false;

    fileContent = strStream.str();
    strStream.str("");
    
    delimFound = false;
    while(ifs.get(c) && !delimFound){
        if (c == '#'){
            delimFound = true;
            break;
        } 
        strStream<<c;
    }
    if(ifs.fail() || !delimFound) return false;

    strTimeSave = strStream.str();
    strStream.str("");

    delimFound = false;
    while(ifs.get(c) && !delimFound){
        if (c == '*'){
            delimFound = true;
            break;
        } 
        if(!isdigit(c)){
            return false;
        }
        strStream<<c;
    }
    if(ifs.fail() || !delimFound) return false;

    strHash = strStream.str();
    strStream.str("");
    ifs.close();
    
    //check hash
    int hash, timeSave;
    try{
        hash = std::stoi(strHash);
        timeSave = std::stoi(strTimeSave);
    }catch(std::out_of_range const& ex){
        return false;
    }

    int correctHash = getHash(fileContent,timeSave);
    if(hash != correctHash){
        return false;
    }

    //read game
    char delimiter = '&';
    std::string::const_iterator it = fileContent.begin();

    //game type
    readNextChunk(strStream, delimiter, fileContent, it);
    gameType = strStream.str();

    //read difficulty (for 2 players game difficulty = 0)
    readNextChunk(strStream,delimiter,fileContent,it);
    difficulty = strStream.str();

    //is Check
    readNextChunk(strStream, delimiter, fileContent, it);
    isCheck = strStream.str();

    //is CheckMate
    readNextChunk(strStream, delimiter, fileContent, it);
    isCheckMate = strStream.str();

    //is Stalmate
    readNextChunk(strStream, delimiter, fileContent, it);
    isStalmate = strStream.str();

    //playing side
    readNextChunk(strStream, delimiter, fileContent, it);
    playingSide = strStream.str();

    //figures 
    readNextChunk(strStream, delimiter, fileContent, it);
    positionIsFreeData = strStream.str();

    readNextChunk(strStream, delimiter, fileContent, it);
    in1  = strStream.str();

    readNextChunk(strStream, delimiter, fileContent, it);
    in2  = strStream.str();

    readNextChunk(strStream, delimiter, fileContent, it);
    out1 = strStream.str();

    readNextChunk(strStream, delimiter, fileContent, it);
    out2 = strStream.str();
 
    return true;
}  

int FileOperations::getHash(std::string & info, long saveTime){
    std::hash<std::string> hasher;
    int hash = hasher(info) + saveTime %123456;
    return abs(hash);
}

void FileOperations::readNextChunk(std::stringstream & strStream, char delimiter, const std::string & fileContent, std::string::const_iterator & it){
    strStream.str("");
    while(*it != delimiter){
        strStream<<*it;
        it++;
    }
    it++;
    it++;
}