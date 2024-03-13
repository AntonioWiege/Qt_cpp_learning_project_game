#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

class characterState{
public:
    ///top & clockwise sides & diagonals; one combined, instead of individual axis members.
    int screenPosState;
    ///which id of cube to show
    int displayState;
    //int score;//destroyed cubes - used cubes
    //int lives=100;//100-used cubes that ran out of level bounds
};

#endif // CHARACTERSTATE_H
