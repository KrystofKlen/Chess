#pragma once
#include "Figure.h"
#include <memory>


class Position{
public:
    int mRowIndex, mColumnIndex;
    std::shared_ptr<Figure> mFigure;
    Position* ptrToPositionOnWhichIsPawnThatCanBeKickedUsingEnPassant = nullptr;
    bool mIsFree = true;
    bool operator == (const Position & rhs ){
        return rhs.mColumnIndex == this->mColumnIndex && rhs.mRowIndex == this->mRowIndex;
    }
    Position(const Position & pos);
    Position();
    
};