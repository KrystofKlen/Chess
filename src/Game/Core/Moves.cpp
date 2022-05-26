#include "Moves.h"

bool breakBecausePositionBlocked(Coordinates coordinates, int side, std::list<Coordinates> & possiblePositions){
    
    if(!Board::playField[coordinates.mRowIndex][coordinates.mColumnIndex].mIsFree){
        if(Board::playField[coordinates.mRowIndex][coordinates.mColumnIndex].mFigure->mSide == side){
            return true;
        }else{
            possiblePositions.push_back(coordinates);
            return true;
        }
    }
    return false;  
}


void addMovesVertical(std::list<Coordinates> & possiblePositions, const Figure & figure){
    int i;
    
    for(i = 1; i <= figure.mMaxNumberOfSteps ; i++){

        if(figure.mCoordinates.mRowIndex + i <  8){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex + i, figure.mCoordinates.mColumnIndex}, 
                figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back(
                    {figure.mCoordinates.mRowIndex + i,figure.mCoordinates.mColumnIndex});
        }
    }

    for(i = 1; i <= figure.mMaxNumberOfSteps ; i++){
        if(figure.mCoordinates.mRowIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex - i, figure.mCoordinates.mColumnIndex},
                 figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({figure.mCoordinates.mRowIndex - i, figure.mCoordinates.mColumnIndex});
        }
    }
}

void addMovesHorizontal(std::list<Coordinates> & possiblePositions, const Figure & figure){
    
    int i;
    for(i = 1; i <= figure.mMaxNumberOfSteps; i++){

        if(figure.mCoordinates.mColumnIndex + i < 8){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex , figure.mCoordinates.mColumnIndex + i},
                 figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({figure.mCoordinates.mRowIndex, figure.mCoordinates.mColumnIndex + i});
        } 
    }

    for(i = 1; i <= figure.mMaxNumberOfSteps; i++){
        if(figure.mCoordinates.mColumnIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex , figure.mCoordinates.mColumnIndex - i},
                 figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({figure.mCoordinates.mRowIndex, figure.mCoordinates.mColumnIndex  - i});
        } 
    }
 
}

void addMoves1Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure){
    for(int i = 1; i <= figure.mMaxNumberOfSteps; i++){
        if(figure.mCoordinates.mColumnIndex + i < 8 && figure.mCoordinates.mRowIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex - i, figure.mCoordinates.mColumnIndex + i }, 
                figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({figure.mCoordinates.mRowIndex - i, figure.mCoordinates.mColumnIndex + i });
        }
    }
}

void addMoves2Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure){
    for(int i = 1; i <= figure.mMaxNumberOfSteps; i++){
        if(figure.mCoordinates.mColumnIndex - i >= 0 && figure.mCoordinates.mRowIndex - i >= 0){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex - i, figure.mCoordinates.mColumnIndex - i},
                 figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back(
                    {figure.mCoordinates.mRowIndex - i, figure.mCoordinates.mColumnIndex - i}
                );
        }
    }
}

void addMoves3Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure){
    for(int i = 1; i <= figure.mMaxNumberOfSteps; i++){
        if(figure.mCoordinates.mColumnIndex - i >= 0 && figure.mCoordinates.mRowIndex + i < 8){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex + i, figure.mCoordinates.mColumnIndex - i},
                 figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back({figure.mCoordinates.mRowIndex + i, figure.mCoordinates.mColumnIndex - i});
        }
    }
}

void addMoves4Quadrant(std::list<Coordinates> & possiblePositions, const Figure & figure){
    for(int i = 1; i <= figure.mMaxNumberOfSteps; i++){
        if(figure.mCoordinates.mColumnIndex + i < 8 && figure.mCoordinates.mRowIndex + i < 8){
            if (breakBecausePositionBlocked(
                {figure.mCoordinates.mRowIndex + i, figure.mCoordinates.mColumnIndex + i },
                figure.mSide, possiblePositions))
                break;
            else
                possiblePositions.push_back( {figure.mCoordinates.mRowIndex + i, figure.mCoordinates.mColumnIndex + i });
        }
    }
}

void addQuadrantsForPawnSide1(std::list<Coordinates> & possiblePositions, const Figure & figure){

    if( figure.mCoordinates.mColumnIndex - 1 >= 0 && figure.mCoordinates.mRowIndex + 1 < 8 &&
        !Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex - 1].mIsFree && 
    Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex - 1].mFigure->mSide != figure.mSide){
        possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex - 1});
    }

    if( figure.mCoordinates.mColumnIndex + 1 < 8 && figure.mCoordinates.mRowIndex + 1 < 8 &&
        !Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex + 1].mIsFree && 
    Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex + 1].mFigure->mSide != figure.mSide){
        possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex + 1});
    }    
}

void addQuadrantsForPawnSide2(std::list<Coordinates> & possiblePositions, const Figure & figure){
    
    if( figure.mCoordinates.mColumnIndex - 1 >= 0 && figure.mCoordinates.mRowIndex - 1 >= 0 &&
        !Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex - 1].mIsFree && 
        Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex - 1].mFigure->mSide != figure.mSide){
            possiblePositions.push_back({ figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex - 1});
    }
    if( figure.mCoordinates.mColumnIndex + 1 < 8 && figure.mCoordinates.mRowIndex - 1 >= 0 &&
        !Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex + 1].mIsFree && 
    Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex + 1].mFigure->mSide != figure.mSide){
        possiblePositions.push_back({figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex + 1});
    }
}

void addMovesKnight(std::list<Coordinates> & possiblePositions,  const Figure & figure){
    
    if(figure.mCoordinates.mColumnIndex + 2 < 8){
        if(figure.mCoordinates.mRowIndex - 1 >= 0){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex + 2];

            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
                possiblePositions.push_back({figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex + 2});
        }
        if(figure.mCoordinates.mRowIndex + 1 < 8){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex + 2];
            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex + 2});
        }
    }
    if(figure.mCoordinates.mColumnIndex - 2 >= 0){
        if(figure.mCoordinates.mRowIndex - 1 >= 0){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex - 2];

            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex - 2});
        }
        if(figure.mCoordinates.mRowIndex + 1 < 8){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex - 2];
    
            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex - 2});
        }
    }
    if(figure.mCoordinates.mRowIndex + 2 < 8){
        if(figure.mCoordinates.mColumnIndex + 1 < 8){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex + 2][figure.mCoordinates.mColumnIndex + 1];

            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex + 2, figure.mCoordinates.mColumnIndex + 1});
        }
        if(figure.mCoordinates.mColumnIndex - 1 >= 0){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex + 2][figure.mCoordinates.mColumnIndex - 1];
            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex + 2, figure.mCoordinates.mColumnIndex - 1 });
        }
    }
    if(figure.mCoordinates.mRowIndex - 2 >= 0){
        if(figure.mCoordinates.mColumnIndex + 1 < 8){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex - 2][figure.mCoordinates.mColumnIndex + 1];

            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex - 2, figure.mCoordinates.mColumnIndex + 1 });
        }
        if(figure.mCoordinates.mColumnIndex - 1 >= 0){
            Position & posRef = Board::playField[figure.mCoordinates.mRowIndex - 2][figure.mCoordinates.mColumnIndex - 1];

            if(posRef.mIsFree
             || posRef.mFigure->mSide != figure.mSide)
            possiblePositions.push_back({figure.mCoordinates.mRowIndex - 2, figure.mCoordinates.mColumnIndex - 1});
        }
    }
}

void addEnPassantForPawn(std::list<Coordinates> & possiblePositions, const Figure & figure){

    Position & posRef = Board::playField[figure.mCoordinates.mRowIndex][figure.mCoordinates.mColumnIndex - 1];
    Position & posRef2 = Board::playField[figure.mCoordinates.mRowIndex][figure.mCoordinates.mColumnIndex + 1];

    if(figure.mSide == 1 && figure.mCoordinates.mRowIndex == 4){

        if(figure.mCoordinates.mColumnIndex - 1 >= 0 && !Board::playField[figure.mCoordinates.mRowIndex][figure.mCoordinates.mColumnIndex - 1].mIsFree &&
        posRef.mFigure->mLetter == 'P' &&
        posRef.mFigure->mSide != figure.mSide &&
        posRef.mFigure->mNumOfStepsDone == 1 &&
        Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex - 1].mIsFree
        ){
            possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex - 1 });
        }

        if(figure.mCoordinates.mColumnIndex + 1 < 8 && !posRef2.mIsFree &&
        posRef2.mFigure->mLetter == 'P' &&
        posRef2.mFigure->mSide != figure.mSide &&
        posRef2.mFigure->mNumOfStepsDone == 1 &&
        Board::playField[figure.mCoordinates.mRowIndex + 1][figure.mCoordinates.mColumnIndex + 1].mIsFree
        ){
            possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex + 1});
        }
    }

    if(figure.mSide == 2 && figure.mCoordinates.mRowIndex == 3){
        
        if(figure.mCoordinates.mColumnIndex - 1 >= 0 && !posRef.mIsFree &&
        posRef.mFigure->mLetter == 'P' &&
        posRef.mFigure->mSide != figure.mSide &&
        posRef.mFigure->mNumOfStepsDone == 1 &&
        Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex - 1].mIsFree){
            possiblePositions.push_back({ figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex - 1});
            
        }

        if(figure.mCoordinates.mColumnIndex + 1 < 8 && 
        !posRef2.mIsFree &&
        posRef2.mFigure->mLetter == 'P' &&
        posRef2.mFigure->mSide != figure.mSide &&
        posRef2.mFigure->mNumOfStepsDone == 1 &&
        Board::playField[figure.mCoordinates.mRowIndex - 1][figure.mCoordinates.mColumnIndex + 1].mIsFree ){
            possiblePositions.push_back({ figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex + 1});
        }
    }
}

bool checkWayIsFree(CastlingSide side, const Figure & king){
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

void addCastlingPositionsForKing(std::list<Coordinates > & castlingPositions, const Figure & king){

    if(king.mNumOfStepsDone != 0) return;

    int kingSide = king.mSide;
    const Position* posWithRock;

    if(kingSide == 1){
        posWithRock = &Board::playField[0][0];

        if(!posWithRock->mIsFree &&
            posWithRock->mFigure.get()->mLetter == 'R' &&
         posWithRock->mFigure.get()->mNumOfStepsDone == 0 &&
         posWithRock->mFigure.get()->mSide == kingSide &&
         checkWayIsFree( LONGER_SIDE, king ) )
            castlingPositions.push_back({0,2});

        posWithRock = &Board::playField[0][7];

        if(!posWithRock->mIsFree &&
            posWithRock->mFigure.get()->mLetter == 'R' && 
        posWithRock->mFigure.get()->mNumOfStepsDone == 0 &&
        posWithRock->mFigure.get()->mSide == kingSide  &&
        checkWayIsFree( SHORTER_SIDE, king ))
            castlingPositions.push_back({0,6});
    }

    if(kingSide == 2){
        posWithRock = &Board::playField[7][0];

        if(!posWithRock->mIsFree &&
            posWithRock->mFigure.get()->mLetter == 'R' &&
         posWithRock->mFigure.get()->mNumOfStepsDone == 0 &&
         posWithRock->mFigure.get()->mSide == kingSide &&
         checkWayIsFree( LONGER_SIDE, king ))
            castlingPositions.push_back({7,2});

        posWithRock = &Board::playField[7][7];

        if(!posWithRock->mIsFree &&
            posWithRock->mFigure.get()->mLetter == 'R' &&
         posWithRock->mFigure.get()->mNumOfStepsDone == 0 &&
         posWithRock->mFigure.get()->mSide == kingSide &&
         checkWayIsFree( SHORTER_SIDE, king ))
            castlingPositions.push_back({7,6});
    }
}


void addPawnPossibleKickoutsSide1(std::list<Coordinates> & possiblePositions, const Figure & figure){

    if( figure.mCoordinates.mColumnIndex - 1 >= 0 && figure.mCoordinates.mRowIndex + 1 < 8 ){
        possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex - 1});
    }

    if( figure.mCoordinates.mColumnIndex + 1 < 8 && figure.mCoordinates.mRowIndex + 1 < 8 ){
        possiblePositions.push_back({figure.mCoordinates.mRowIndex + 1, figure.mCoordinates.mColumnIndex + 1});
    }    
}

void addPawnPossibleKickoutsSide2(std::list<Coordinates> & possiblePositions, const Figure & figure){
    
    if( figure.mCoordinates.mColumnIndex - 1 >= 0 && figure.mCoordinates.mRowIndex - 1 >= 0){
            possiblePositions.push_back({ figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex - 1});
    }
    if( figure.mCoordinates.mColumnIndex + 1 < 8 && figure.mCoordinates.mRowIndex - 1 >= 0){
        possiblePositions.push_back({figure.mCoordinates.mRowIndex - 1, figure.mCoordinates.mColumnIndex + 1});
    }
}