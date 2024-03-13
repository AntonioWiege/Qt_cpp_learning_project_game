#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "cube.h"
#include "stage.h"
#include "audiohandler.h"

#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QString>
#include <QFont>
#include <QBrush>
#include <QImage>
#include <QTime>
#include <QObject>

class game: public QGraphicsView{
    Q_OBJECT
public:
    game(QWidget * parent=0);

    bool isRunning;
    QGraphicsScene * scene;
    audioHandler * audio;

    void play();
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    void keyPressEvent(QKeyEvent * event);

    void updatePlayerPos(QMouseEvent *event);
    void shootCube();
    void scrollAmmoType();
    void cheat(QKeyEvent *event);
    
public slots:
    void projectileMovementTick();
    void updateScore();

private:
    character * player_character;
    QGraphicsLineItem * debugLineArray[3];
    QGraphicsPixmapItem * field;
    QGraphicsRectItem * fogLayers[12];
    cube * shotCubes[8];
    stage * demoStage;
    QLabel * score;

    void update();
    void setupScene();
    //void setupDebugging();
    void createPlayerCharacter();
    void setupLevel();
    void removeShot(int i);

    void certainCubeDelete(cube * c);
};

#endif // GAME_H
