#ifndef STAGE_H
#define STAGE_H

#include "audiohandler.h"
#include "cube.h"

class stage: public QObject
{
        Q_OBJECT
public:
    stage(audioHandler * audioInstance);

    audioHandler * audioInstance;
    ///entire map, levels stacked, rise up & generate at progress
    cube * cubes[10][8][12];
    ///level
    int raiseCounter=0;

public slots:
    void checkMap();
};

#endif // STAGE_H
