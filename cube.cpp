#include "cube.h"

cube::cube(QPointF pos, char t,QGraphicsScene * scene, float depth) {
    setDetails(pos.x(),pos.y(),t,scene,depth);
}

char cube::intToCubeType(int i)
{
    switch(abs(i%8)){
    case 0:
        return 'R';
    case 1:
        return 'O';
    case 2:
        return 'Y';
    case 3:
        return 'T';
    case 4:
        return 'G';
    case 5:
        return 'C';
    case 6:
        return 'B';
    case 7:
        return 'M';
    default:
        return ' ';
    }
}

cube::cube(int x, int y, char t,QGraphicsScene * scene, float depth) {
    setDetails(x,y,t,scene,depth);
}

void cube::setDetails(int x, int y, char t,QGraphicsScene * scene, float depth) {
    setPos(x,y);
    setTransformOriginPoint(24,24);
    typ = t;
    switch(t){
    case 'R':
        setPixmap(QPixmap(":/images/cubeR.png").scaled(48,48));
        break;
    case 'G':
        setPixmap(QPixmap(":/images/cubeG.png").scaled(48,48));
        break;
    case 'B':
        setPixmap(QPixmap(":/images/cubeB.png").scaled(48,48));
        break;
    case 'C':
        setPixmap(QPixmap(":/images/cubeC.png").scaled(48,48));
        break;
    case 'M':
        setPixmap(QPixmap(":/images/cubeM.png").scaled(48,48));
        break;
    case 'Y':
        setPixmap(QPixmap(":/images/cubeY.png").scaled(48,48));
        break;
    case 'O':
        setPixmap(QPixmap(":/images/cubeO.png").scaled(48,48));
        break;
    case 'T':
        setPixmap(QPixmap(":/images/cubeT.png").scaled(48,48));
        break;
    default:
        setPixmap(QPixmap(":/images/cube.png").scaled(48,48));
        typ = 'u';//undefined
        break;
    }
    setTransformOriginPoint(24,24);
    setShapeMode(HeuristicMaskShape);
    if(scene!=nullptr){
        scene->addItem(this);
    }
    if(depth!=0.8699f){
        setZValue(depth);
    }
}

cube* cube::checkCollision()
{
    cube * c = nullptr;
    for(auto item : collidingItems()){
        if(item->type()==type()){
           cube * candidate = dynamic_cast<cube *>(item);
            if(candidate){
               if(candidate->typ == typ && candidate->zValue()==zValue()){
                   c = candidate;
                   break;
               }
           }
        }
    }
    return c;
}
