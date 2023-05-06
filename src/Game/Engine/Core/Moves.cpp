#include "Moves.h"

bool breakBecausePositionBlocked(Coordinates coordinates, int side, std::list<Coordinates> & possiblePositions){
    
    if(!Board::playField[coordinates.mRowIndex][coordinates.mColumnIndex].mIsFree){
        if(Board::playField[coordinates.mRowIndex][coordinates.mColumnIndex].mPiece->mSide == side){
            return true;
        }else{
            possiblePositions.push_back(coordinates);
            return true;
        }
    }
    return false;  
}


void addMovesVerticalAndHorizontal(std::list<Coordinates> & possiblePositions, const Piece & piece, int rowChange, int colChange){
    int i;
    
    for(i = 1; i <= piece.mMaxNumberOfSteps ; i++){
        int newRow = piece.mCoordinates.mRowIndex + (i * rowChange);
        int newCol = piece.mCoordinates.mColumnIndex + (i * colChange);

        if(newRow >= 0 && newRow < Board::BOARD_SIZE && newCol >= 0 && newCol < Board::BOARD_SIZE){
            if (breakBecausePositionBlocked({newRow, newCol}, piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({newRow, newCol});
        }
    }
}

void addMovesVertical(std::list<Coordinates> & possiblePositions, const Piece & piece){
    addMovesVerticalAndHorizontal(possiblePositions, piece, 1, 0);
    addMovesVerticalAndHorizontal(possiblePositions, piece, -1, 0);
}

void addMovesHorizontal(std::list<Coordinates> & possiblePositions, const Piece & piece){
    addMovesVerticalAndHorizontal(possiblePositions, piece, 0, 1);
    addMovesVerticalAndHorizontal(possiblePositions, piece, 0, -1);
}

void addMovesInDirection(std::list<Coordinates> &possiblePositions, const Piece &piece, int rowOffset, int colOffset) {
    for (int i = 1; i <= piece.mMaxNumberOfSteps; i++) {
        int newRow = piece.mCoordinates.mRowIndex + (i * rowOffset);
        int newCol = piece.mCoordinates.mColumnIndex + (i * colOffset);
        if (newRow >= Board::BOARD_SIZE || newCol >= Board::BOARD_SIZE || newRow < 0 || newCol < 0)
            break;
        if (breakBecausePositionBlocked({newRow, newCol}, piece.mSide, possiblePositions))
            break;
        else
            possiblePositions.push_back({newRow, newCol});
    }
}

void addMoves1Quadrant(std::list<Coordinates> &possiblePositions, const Piece &piece) {
    addMovesInDirection(possiblePositions, piece, -1, 1);
}

void addMoves2Quadrant(std::list<Coordinates> &possiblePositions, const Piece &piece) {
    addMovesInDirection(possiblePositions, piece, -1, -1);
}

void addMoves3Quadrant(std::list<Coordinates> &possiblePositions, const Piece &piece) {
    addMovesInDirection(possiblePositions, piece, 1, -1);
}

void addMoves4Quadrant(std::list<Coordinates> &possiblePositions, const Piece &piece) {
    addMovesInDirection(possiblePositions, piece, 1, 1);
}


void addQuadrantsForPawn(std::list<Coordinates>& possiblePositions, const Piece& piece, int rowModifier, int columnModifier) {
    int newRow = piece.mCoordinates.mRowIndex + rowModifier;
    int newCol = piece.mCoordinates.mColumnIndex + columnModifier;

    // check I am within board bounds
    if (newRow >= 0 && newRow < Board::BOARD_SIZE && newCol >= 0 && newCol < Board::BOARD_SIZE) {
        Position& pos = Board::playField[newRow][newCol];
        // if position is occupied by other side, we can add move
        if (!pos.mIsFree && pos.mPiece->mSide != piece.mSide) {
            possiblePositions.push_back({ newRow, newCol });
        }
    }
}

void addQuadrantsForPawnSide1(std::list<Coordinates>& possiblePositions, const Piece& piece) {
    addQuadrantsForPawn(possiblePositions, piece, 1, -1);
    addQuadrantsForPawn(possiblePositions, piece, 1, 1);
}

void addQuadrantsForPawnSide2(std::list<Coordinates>& possiblePositions, const Piece& piece) {
    addQuadrantsForPawn(possiblePositions, piece, -1, -1);
    addQuadrantsForPawn(possiblePositions, piece, -1, 1);
}

void addMovesKnight(std::list<Coordinates> & possiblePositions,  const Piece & piece){
    int rowOffsets[] = {-1, -1, 1, 1, -2, -2, 2, 2};
    int colOffsets[] = {2, -2, 2, -2, 1, -1, 1, -1};
    int maxPossibleMovesKnightCanHave = 8;

    for(int i = 0; i < maxPossibleMovesKnightCanHave; i++){
        int newRow = piece.mCoordinates.mRowIndex + rowOffsets[i];
        int newCol = piece.mCoordinates.mColumnIndex + colOffsets[i];

        if(newRow >= 0 && newRow < Board::BOARD_SIZE && newCol >= 0 && newCol < Board::BOARD_SIZE){
            Position & posRef = Board::playField[newRow][newCol];

            if(posRef.mIsFree || posRef.mPiece->mSide != piece.mSide){
                possiblePositions.push_back({newRow, newCol});
            }
        }
    }
}


bool canEnPassantCapture(const Piece& piece, int dx, int dy) {
    int row = piece.mCoordinates.mRowIndex;
    int col = piece.mCoordinates.mColumnIndex;
    int side = piece.mSide;
    Position& posRef = Board::playField[row][col + dx];
    return row == (side == 1 ? 4 : 3) && col + dx >= 0 && col + dx < Board::BOARD_SIZE
        && !posRef.mIsFree && posRef.mPiece->mLetter == PAWN && posRef.mPiece->mSide != side
        && posRef.mPiece->mNumOfStepsDone == 1 && Board::playField[row + dy][col + dx].mIsFree;
}


void addEnPassantForPawn(std::list<Coordinates>& possiblePositions, const Piece& piece) {

    if (canEnPassantCapture(piece, -1, 1)) {
        possiblePositions.push_back({ piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex - 1 });
    }

    if (canEnPassantCapture(piece, 1, 1)) {
        possiblePositions.push_back({ piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex + 1 });
    }

    if (canEnPassantCapture(piece, -1, -1)) {
        possiblePositions.push_back({ piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex - 1 });
    }

    if (canEnPassantCapture(piece, 1, -1)) {
        possiblePositions.push_back({ piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex + 1 });
    }
}

bool checkWayIsFree(CastlingSide side, const Piece & king){
    int kingColumnIndex;
    if(king.mSide == 1 && side == SHORTER_SIDE){
        for(kingColumnIndex = king.mCoordinates.mColumnIndex + 1; kingColumnIndex < 7; kingColumnIndex++){
            if( !Board::playField[0][kingColumnIndex].mIsFree) return false;
        }
        return true;
    }
    if(king.mSide == 1 && side == LONGER_SIDE){
        for(kingColumnIndex = king.mCoordinates.mColumnIndex - 1; kingColumnIndex > 0; kingColumnIndex--){
            if( !Board::playField[0][kingColumnIndex].mIsFree) return false;
        }
        return true;
    }
    if(king.mSide == 2 && side == SHORTER_SIDE){
        for(kingColumnIndex = king.mCoordinates.mColumnIndex + 1; kingColumnIndex < 7; kingColumnIndex++){
            if( !Board::playField[7][kingColumnIndex].mIsFree) return false;
        }
        return true;
    }
    if(king.mSide == 2 && side == LONGER_SIDE){
        for(kingColumnIndex= king.mCoordinates.mColumnIndex - 1; kingColumnIndex > 0; kingColumnIndex--){
            if( !Board::playField[7][kingColumnIndex].mIsFree) return false;
        }
        return true;
    }
    return false;
}

void addCastlingPositionsForKing(std::list<Coordinates > & castlingPositions, const Piece & king){

    if(king.mNumOfStepsDone != 0) return;

    int kingSide = king.mSide;
    const Position* posWithRock;

    if(kingSide == 1){
        posWithRock = &Board::playField[0][0];

        if(!posWithRock->mIsFree &&
            posWithRock->mPiece.get()->mLetter == ROCK &&
         posWithRock->mPiece.get()->mNumOfStepsDone == 0 &&
         posWithRock->mPiece.get()->mSide == kingSide &&
         checkWayIsFree( LONGER_SIDE, king ) )
            castlingPositions.push_back({0,2});

        posWithRock = &Board::playField[0][7];

        if(!posWithRock->mIsFree &&
            posWithRock->mPiece.get()->mLetter == ROCK && 
        posWithRock->mPiece.get()->mNumOfStepsDone == 0 &&
        posWithRock->mPiece.get()->mSide == kingSide  &&
        checkWayIsFree( SHORTER_SIDE, king ))
            castlingPositions.push_back({0,6});
    }

    if(kingSide == 2){
        posWithRock = &Board::playField[7][0];

        if(!posWithRock->mIsFree &&
            posWithRock->mPiece.get()->mLetter == ROCK &&
         posWithRock->mPiece.get()->mNumOfStepsDone == 0 &&
         posWithRock->mPiece.get()->mSide == kingSide &&
         checkWayIsFree( LONGER_SIDE, king ))
            castlingPositions.push_back({7,2});

        posWithRock = &Board::playField[7][7];

        if(!posWithRock->mIsFree &&
            posWithRock->mPiece.get()->mLetter == ROCK &&
         posWithRock->mPiece.get()->mNumOfStepsDone == 0 &&
         posWithRock->mPiece.get()->mSide == kingSide &&
         checkWayIsFree( SHORTER_SIDE, king ))
            castlingPositions.push_back({7,6});
    }
}


void addPawnPossibleKickoutsSide1(std::list<Coordinates> & possiblePositions, const Piece & piece){

    if( piece.mCoordinates.mColumnIndex - 1 >= 0 && piece.mCoordinates.mRowIndex + 1 < Board::BOARD_SIZE ){
        possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex - 1});
    }

    if( piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE && piece.mCoordinates.mRowIndex + 1 < Board::BOARD_SIZE ){
        possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex + 1});
    }    
}

void addPawnPossibleKickoutsSide2(std::list<Coordinates> & possiblePositions, const Piece & piece){
    
    if( piece.mCoordinates.mColumnIndex - 1 >= 0 && piece.mCoordinates.mRowIndex - 1 >= 0){
            possiblePositions.push_back({ piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex - 1});
    }
    if( piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE && piece.mCoordinates.mRowIndex - 1 >= 0){
        possiblePositions.push_back({piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex + 1});
    }
}