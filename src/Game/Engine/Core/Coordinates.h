#pragma once

class Coordinates{
public:
    int mRowIndex;
    int mColumnIndex;
    bool operator == (Coordinates rhs);
    void operator = (Coordinates rhs);
    void setCoordinates(const Coordinates);
   
};