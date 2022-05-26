#include "Coordinates.h"

bool Coordinates::operator == (Coordinates rhs){
    return (mRowIndex == rhs.mRowIndex && mColumnIndex == rhs.mColumnIndex);
}
void Coordinates::operator= (Coordinates rhs){
    mRowIndex = rhs.mRowIndex;
    mColumnIndex = rhs.mColumnIndex;
}
void Coordinates::setCoordinates(const Coordinates rhs){
    mRowIndex = rhs.mRowIndex;
    mColumnIndex = rhs.mColumnIndex;
}