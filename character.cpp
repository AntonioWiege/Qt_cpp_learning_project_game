#include "character.h"
#include <QTimer>

character::character(QGraphicsItem *parent):QGraphicsPixmapItem(parent){
    setPos(400,48);
    setPixmap(QPixmap(":/images/extruder.png").scaled(96,96));
    setTransformOriginPoint(48*2/3,48*2/3);
    charState.displayState='O';
    display = new cube(24,0,charState.displayState);
    display->setParentItem(this);
}
