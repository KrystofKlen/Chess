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


void addMovesVertical(std::list<Coordinates> & possiblePositions, const Piece & piece){
    int i;
    
    for(i = 1; i <= piece.mMaxNumberOfSteps ; i++){

        if(piece.mCoordinates.mRowIndex + i <  Board::BOARD_SIZE){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex + i, piece.mCoordinates.mColumnIndex}, 
                piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back(
                    {piece.mCoordinates.mRowIndex + i,piece.mCoordinates.mColumnIndex});
        }
    }

    for(i = 1; i <= piece.mMaxNumberOfSteps ; i++){
        if(piece.mCoordinates.mRowIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex - i, piece.mCoordinates.mColumnIndex},
                 piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({piece.mCoordinates.mRowIndex - i, piece.mCoordinates.mColumnIndex});
        }
    }
}

void addMovesHorizontal(std::list<Coordinates> & possiblePositions, const Piece & piece){
    
    int i;
    for(i = 1; i <= piece.mMaxNumberOfSteps; i++){

        if(piece.mCoordinates.mColumnIndex + i < Board::BOARD_SIZE){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex , piece.mCoordinates.mColumnIndex + i},
                 piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({piece.mCoordinates.mRowIndex, piece.mCoordinates.mColumnIndex + i});
        } 
    }

    for(i = 1; i <= piece.mMaxNumberOfSteps; i++){
        if(piece.mCoordinates.mColumnIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex , piece.mCoordinates.mColumnIndex - i},
                 piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({piece.mCoordinates.mRowIndex, piece.mCoordinates.mColumnIndex  - i});
        } 
    }
 
}

void addMoves1Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece){
    for(int i = 1; i <= piece.mMaxNumberOfSteps; i++){
        if(piece.mCoordinates.mColumnIndex + i < Board::BOARD_SIZE && piece.mCoordinates.mRowIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex - i, piece.mCoordinates.mColumnIndex + i }, 
                piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({piece.mCoordinates.mRowIndex - i, piece.mCoordinates.mColumnIndex + i });
        }
    }
}

void addMoves2Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece){
    for(int i = 1; i <= piece.mMaxNumberOfSteps; i++){
        if(piece.mCoordinates.mColumnIndex - i >= 0 && piece.mCoordinates.mRowIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex - i, piece.mCoordinates.mColumnIndex - i},
                 piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back(
                    {piece.mCoordinates.mRowIndex - i, piece.mCoordinates.mColumnIndex - i}
                );
        }
    }
}

void addMoves3Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece){
    for(int i = 1; i <= piece.mMaxNumberOfSteps; i++){
        if(piece.mCoordinates.mColumnIndex - i >= 0 && piece.mCoordinates.mRowIndex + i < Board::BOARD_SIZE){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex + i, piece.mCoordinates.mColumnIndex - i},
                 piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({piece.mCoordinates.mRowIndex + i, piece.mCoordinates.mColumnIndex - i});
        }
    }
}

void addMoves4Quadrant(std::list<Coordinates> & possiblePositions, const Piece & piece){
    for(int i = 1; i <= piece.mMaxNumberOfSteps; i++){
        if(piece.mCoordinates.mColumnIndex + i < Board::BOARD_SIZE && piece.mCoordinates.mRowIndex + i < Board::BOARD_SIZE){
            if (breakBecausePositionBlocked(
                {piece.mCoordinates.mRowIndex + i, piece.mCoordinates.mColumnIndex + i },
                piece.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back( {piece.mCoordinates.mRowIndex + i, piece.mCoordinates.mColumnIndex + i });
        }
    }
}

void addQuadrantsForPawnSide1(std::list<Coordinates> & possiblePositions, const Piece & piece){

    if( piece.mCoordinates.mColumnIndex - 1 >= 0 && piece.mCoordinates.mRowIndex + 1 < Board::BOARD_SIZE &&
        !Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex - 1].mIsFree && 
    Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex - 1].mPiece->mSide != piece.mSide){
        possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex - 1});
    }

    if( piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE && piece.mCoordinates.mRowIndex + 1 < Board::BOARD_SIZE &&
        !Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex + 1].mIsFree && 
    Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex + 1].mPiece->mSide != piece.mSide){
        possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex + 1});
    }    
}

void addQuadrantsForPawnSide2(std::list<Coordinates> & possiblePositions, const Piece & piece){
    
    if( piece.mCoordinates.mColumnIndex - 1 >= 0 && piece.mCoordinates.mRowIndex - 1 >= 0 &&
        !Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex - 1].mIsFree && 
        Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex - 1].mPiece->mSide != piece.mSide){
            possiblePositions.push_back({ piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex - 1});
    }
    if( piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE && piece.mCoordinates.mRowIndex - 1 >= 0 &&
        !Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex + 1].mIsFree && 
    Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex + 1].mPiece->mSide != piece.mSide){
        possiblePositions.push_back({piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex + 1});
    }
}

void addMovesKnight(std::list<Coordinates> & possiblePositions,  const Piece & piece){
    
    if(piece.mCoordinates.mColumnIndex + 2 < Board::BOARD_SIZE){
        if(piece.mCoordinates.mRowIndex - 1 >= 0){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex + 2];

            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
                possiblePositions.push_back({piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex + 2});
        }
        if(piece.mCoordinates.mRowIndex + 1 < Board::BOARD_SIZE){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex + 2];
            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex + 2});
        }
    }
    if(piece.mCoordinates.mColumnIndex - 2 >= 0){
        if(piece.mCoordinates.mRowIndex - 1 >= 0){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex - 2];

            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex - 2});
        }
        if(piece.mCoordinates.mRowIndex + 1 < Board::BOARD_SIZE){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex - 2];
    
            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex - 2});
        }
    }
    if(piece.mCoordinates.mRowIndex + 2 < Board::BOARD_SIZE){
        if(piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex + 2][piece.mCoordinates.mColumnIndex + 1];

            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex + 2, piece.mCoordinates.mColumnIndex + 1});
        }
        if(piece.mCoordinates.mColumnIndex - 1 >= 0){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex + 2][piece.mCoordinates.mColumnIndex - 1];
            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex + 2, piece.mCoordinates.mColumnIndex - 1 });
        }
    }
    if(piece.mCoordinates.mRowIndex - 2 >= 0){
        if(piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex - 2][piece.mCoordinates.mColumnIndex + 1];

            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex - 2, piece.mCoordinates.mColumnIndex + 1 });
        }
        if(piece.mCoordinates.mColumnIndex - 1 >= 0){
            Position & posRef = Board::playField[piece.mCoordinates.mRowIndex - 2][piece.mCoordinates.mColumnIndex - 1];

            if(posRef.mIsFree
             || posRef.mPiece->mSide != piece.mSide)
            possiblePositions.push_back({piece.mCoordinates.mRowIndex - 2, piece.mCoordinates.mColumnIndex - 1});
        }
    }
}

void addEnPassantForPawn(std::list<Coordinates> & possiblePositions, const Piece & piece){

    Position & posRef = Board::playField[piece.mCoordinates.mRowIndex][piece.mCoordinates.mColumnIndex - 1];
    Position & posRef2 = Board::playField[piece.mCoordinates.mRowIndex][piece.mCoordinates.mColumnIndex + 1];

    if(piece.mSide == 1 && piece.mCoordinates.mRowIndex == 4){

        if(piece.mCoordinates.mColumnIndex - 1 >= 0 && !Board::playField[piece.mCoordinates.mRowIndex][piece.mCoordinates.mColumnIndex - 1].mIsFree &&
        posRef.mPiece->mLetter == PAWN &&
        posRef.mPiece->mSide != piece.mSide &&
        posRef.mPiece->mNumOfStepsDone == 1 &&
        Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex - 1].mIsFree
        ){
            possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex - 1 });
        }

        if(piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE && !posRef2.mIsFree &&
        posRef2.mPiece->mLetter == PAWN &&
        posRef2.mPiece->mSide != piece.mSide &&
        posRef2.mPiece->mNumOfStepsDone == 1 &&
        Board::playField[piece.mCoordinates.mRowIndex + 1][piece.mCoordinates.mColumnIndex + 1].mIsFree
        ){
            possiblePositions.push_back({piece.mCoordinates.mRowIndex + 1, piece.mCoordinates.mColumnIndex + 1});
        }
    }

    if(piece.mSide == 2 && piece.mCoordinates.mRowIndex == 3){
        
        if(piece.mCoordinates.mColumnIndex - 1 >= 0 && !posRef.mIsFree &&
        posRef.mPiece->mLetter == PAWN &&
        posRef.mPiece->mSide != piece.mSide &&
        posRef.mPiece->mNumOfStepsDone == 1 &&
        Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex - 1].mIsFree){
            possiblePositions.push_back({ piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex - 1});
            
        }

        if(piece.mCoordinates.mColumnIndex + 1 < Board::BOARD_SIZE && 
        !posRef2.mIsFree &&
        posRef2.mPiece->mLetter == PAWN &&
        posRef2.mPiece->mSide != piece.mSide &&
        posRef2.mPiece->mNumOfStepsDone == 1 &&
        Board::playField[piece.mCoordinates.mRowIndex - 1][piece.mCoordinates.mColumnIndex + 1].mIsFree ){
            possiblePositions.push_back({ piece.mCoordinates.mRowIndex - 1, piece.mCoordinates.mColumnIndex + 1});
        }
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