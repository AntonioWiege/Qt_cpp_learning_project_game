#ifndef CHARACTER_H
#define CHARACTER_H

#include "cube.h"
#include "characterState.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>

class character:public QObject, public QGraphicsPixmapItem{
        Q_OBJECT
public:
    character(QGraphicsItem * parent=0);
    ///current ammo type
    cube * display;
    characterState charState;
};

#endif // CHARACTER_H
