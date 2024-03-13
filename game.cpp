#include "game.h"

game::game(QWidget * parent){
    setMouseTracking(true);
}

void game::play(){
    isRunning=false;
    audio = new audioHandler();
    setupScene();
    //setupDebugging();
    createPlayerCharacter();
    player_character->setFocus();
    setupLevel();
    isRunning=true;
    show();
    audio->playMusic(QUrl("qrc:/audio/Antonio Wiege - Drum Up.ogg"));
    wheelEvent(nullptr);
}

void game::setupScene(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setBackgroundBrush(QBrush(QImage(":/images/bgTile.png")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    field = new QGraphicsPixmapItem();
    field->setPos(100,75);
    field->setPixmap(QPixmap(":/images/stageBackdrop.png").scaled(600,450));
    field->setZValue(-13);
    scene->addItem(field);
}
/*
void game::setupDebugging(){
    QPen pen;
    QColor col = QColor(1,1,1,1);
    for(int i = 0; i < 3;i++){
        debugLineArray[i] = new QGraphicsLineItem();
        scene->addItem(debugLineArray[i]);
        pen = debugLineArray[i]->pen();
        pen.setWidth(2);
        col.setHsvF(1.0/12.0*(float)i,1.0,1.0,0.5);
        pen.setColor(col);
        debugLineArray[i]->setPen(pen);
    }
}*/

void game::createPlayerCharacter(){
    player_character = new character();
    scene->addItem(player_character);
    player_character->setFlag(QGraphicsItem::ItemIsFocusable);
}

void game::setupLevel(){

    demoStage = new stage(audio);

    int offset = rand()%8;

    for(int p = 1;p<11;p++){
        for(int o = 1;o<7;o++){
            for(int i = 1;i<9;i++){
                if(rand() % 100>20){
                    demoStage->cubes[i][o][p]=nullptr;
                }else{
                    int x = 400-48*5+i*48;
                    int y = 300-48*4+o*48;
                    int b = (i+o+p)/(p);
                    demoStage->cubes[i][o][p] = new cube(x,y,
                                                         cube::intToCubeType(offset+b)
                                                         ,scene,-13.0+p);
                }
            }
        }
    }

    for(int i = 0;i<12;i++){
        fogLayers[i] = new QGraphicsRectItem();
        fogLayers[i]->setRect(100,75,600,450);
        QBrush brush = Qt::black;
        brush.setColor(QColor(30,30,30,80/(12-i)));
        fogLayers[i]->setBrush(brush);
        fogLayers[i]->setZValue(-15.0+i);
        scene->addItem(fogLayers[i]);
    }

    for(int i = 0;i<8;i++){
        shotCubes[i]=nullptr;
    }

    QTimer* timerShoot = new QTimer(this);
    connect(timerShoot,SIGNAL(timeout()),this,SLOT(shoot()));

    timerShoot->start(10);

    QTimer* timerStageCheck = new QTimer(this);
    connect(timerStageCheck,SIGNAL(timeout()),demoStage,SLOT(checkMap()));
    connect(timerStageCheck,SIGNAL(timeout()),this,SLOT(updateScore()));
    timerStageCheck->start(1000);

    score = new QLabel(this);
    score->setGeometry(380,0,100,50);
    auto f = score->font();
    f.setPointSize(16);
    score->setFont(f);
    score->show();
}



void game::mouseMoveEvent(QMouseEvent *event)
{
    //
    // FIGURE OUT THE RIGHT WAY TO HANDLE ORIGINS
    //

    updatePlayerPos(event);
}
void game::mousePressEvent(QMouseEvent *event){
    shootCube();
}
void game::wheelEvent(QWheelEvent *event)
{
    scrollAmmoType();
}
void game::keyPressEvent(QKeyEvent *event)
{
    cheat(event);
}


void game::updatePlayerPos(QMouseEvent *event)
{
    player_character->setZValue(1);

    auto p = event->pos();
    double x = ((p.x()/800.0)-0.5);
    double y = ((p.y()/600.0)-0.5);
    double ax = abs(x);
    double ay = abs(y);

    if(abs(abs(x)-abs(y))<0.016){ //determines whether to treat diagonal or not
        if(x>0&&y>0){
            x=800+32;
            y=600;
            player_character->setRotation(90+45);
            player_character->charState.screenPosState=3;
            //bottomright
        }else if(x>0&&y<0){
            x=800;
            y=-32;
            player_character->setRotation(90-45);
            player_character->charState.screenPosState=1;
            //topright
        }else if(x<0&&y<0){
            x=-32;
            y=0;
            player_character->setRotation(90+45+180);
            player_character->charState.screenPosState=7;
            //topleft
        }else{
            x=0;
            y=632;
            player_character->setRotation(90-45+180);
            player_character->charState.screenPosState=5;
            //bottomleft
        }
        x+=x<400?32:-32;
        y+=y<300?32:-32;

    }else{
        if(y<0 && ay>=ax){
            x=p.x();
            y=0;
            player_character->setRotation(0);
            player_character->charState.screenPosState=0;
        }else if(x>=0 && ax>=ay){
            x=800;
            y=p.y();
            player_character->setRotation(90);
            player_character->charState.screenPosState=2;
        }else if(y>=0 && ay>=ax){
            x=p.x();
            y=600;
            player_character->setRotation(180);
            player_character->charState.screenPosState=4;
        }else{
            x=0;
            y=p.y();
            player_character->setRotation(270);
            player_character->charState.screenPosState=6;
        }
        //x+=x<400?32:-32;
        //y+=y<300?32:-32;
    }

    player_character->setPos(QPoint(x,y)+QPoint(-32,-32));
}


void game::shootCube()
{
    auto cub = new cube(player_character->pos(),cube::intToCubeType(player_character->charState.displayState),scene,
                        (demoStage->raiseCounter>9)?-4:-3);

    for(int i = 0;i<8;i++){
        if(shotCubes[i]==nullptr){
            shotCubes[i] = cub;
            break;
        }
    }

    audio->playSFXBufferA(QUrl("qrc:/audio/shot.wav"));
}

void game::scrollAmmoType()
{
    player_character->charState.displayState++;
    delete player_character->display;
    player_character->display = new cube(24,0,cube::intToCubeType(player_character->charState.displayState));
    player_character->display->setParentItem(player_character);
}

void game::cheat(QKeyEvent *event)
{
    if (event->key() == Qt::Key_P){
        for(int t = 0; t < 10; t++){
            for(int p =10;p<11;p++){
                for(int o = 1;o<7;o++){
                    for(int i = 1;i<9;i++){
                        if(demoStage->cubes[i][o][p]!=nullptr){
                            certainCubeDelete(demoStage->cubes[i][o][p]);
                            demoStage->cubes[i][o][p]=nullptr;
                        }
                    }
                }
            }
            demoStage->checkMap();
        }
    }
}

void game::updateScore()
{
    score->setText(QStringLiteral("Score:%1").arg(demoStage->raiseCounter));
}

void game::projectileMovementTick()
{
    //! Behavior is cool. Now magnet gel based
    for(int i = 0;i<8;i++){
        if(shotCubes[i]!=nullptr){
            auto x = shotCubes[i]->pos().x();
            auto y = shotCubes[i]->pos().y();
            switch(player_character->charState.screenPosState){
            case 0:
                shotCubes[i]->moveBy(0,10);
                if(y>600){
                    removeShot(i); }
                break;
            case 1:
                shotCubes[i]->moveBy(-10,10);
                if(x<0||y>600){
                    removeShot(i);}
                break;
            case 2:
                shotCubes[i]->moveBy(-10,0);
                if(x<0){
                    removeShot(i); }
                break;
            case 3:
                shotCubes[i]->moveBy(-10,-10);
                if(y<0||x<0){
                    removeShot(i); }
                break;
            case 4:
                shotCubes[i]->moveBy(0,-10);
                if(y<0){
                    removeShot(i);}
                break;
            case 5:
                shotCubes[i]->moveBy(10,-10);
                if(x>800||y<0){
                    removeShot(i); }
                break;
            case 6:
                shotCubes[i]->moveBy(10,0);
                if(x>800){
                    removeShot(i);}
                break;
            case 7:
                shotCubes[i]->moveBy(10,10);
                if(x>800||y>600){
                    removeShot(i);   }
                break;
            }
            if(shotCubes[i]!=nullptr){
                cube* collider = shotCubes[i]->checkCollision();
                if(collider!=nullptr){
                    certainCubeDelete(shotCubes[i]);
                    certainCubeDelete(collider);
                }
            }
        }
    }
}

void game::removeShot(int i){
    scene->removeItem(shotCubes[i]);
    delete shotCubes[i];
    shotCubes[i] = nullptr;
    audio->playSFXBufferA(QUrl("qrc:/audio/damage.wav"));
}

///summary
/// goes through all cube collections and makes sure to set all references to nullptr
/// to properly remove all pointers from memory that will be deleted
void game::certainCubeDelete(cube *c)
{
    if(c==nullptr)return;

    for(int o = 0;o<8;o++){
        if(shotCubes[o]==c){
            shotCubes[o] = nullptr;
        }
    }

    for(int p = 0;p<12;p++){
        for(int o = 0;o<8;o++){
            for(int i = 0;i<10;i++){
                if(demoStage->cubes[i][o][p]==c){
                    demoStage->cubes[i][o][p] = nullptr;
                }
            }
        }
    }

    delete c;

    audio->playSFXBufferA(QUrl("qrc:/audio/cubeDstr.wav"));
}
