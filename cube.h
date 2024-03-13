#ifndef CUBE_H
#define CUBE_H

#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QTime>
#include <QObject>

class cube :public QGraphicsPixmapItem
{
public:
    cube(int x, int y, char t=' ',QGraphicsScene * scene=nullptr, float depth = 0.8699f);
    cube(QPointF pos, char t=' ',QGraphicsScene * scene=nullptr, float depth = 0.8699f);

    static char intToCubeType(int i);

    void setDetails(int x, int y, char t,QGraphicsScene * scene=nullptr, float depth = 0.8699f);
    ///overlaying elements, only valid for same CubeType
    cube* checkCollision();

    char typ;
    //bool isShot;//moving in field
    //bool isFalling;//moving in depth
};



#endif // CUBE_H
