#include "stage.h"
#include "iostream"

stage::stage(audioHandler * audioInstance) {
    for(int p = 0;p<12;p++){
        for(int o = 0;o<8;o++){
            for(int i = 0;i<10;i++){
                cubes[i][o][p]=nullptr;
            }
        }
    }
    this->audioInstance=audioInstance;
}
///go through top layer. If empty, move all lower levels up and generate a new at the bottom
void stage::checkMap()
{
    bool empty = true;
    for(int p = 10;p<11;p++){
        for(int o = 1;o<7;o++){
            for(int i = 1;i<9;i++){
                if(cubes[i][o][p]!=nullptr)empty=false;
            }
        }
    }
    if(empty){
        cube* someCube;
        for(int p = 10;p>0;p--){
            for(int o = 1;o<7;o++){
                for(int i = 1;i<9;i++){
                    cubes[i][o][p]=cubes[i][o][p-1];
                    if(cubes[i][o][p]!=nullptr){
                        cubes[i][o][p]->setZValue(cubes[i][o][p]->zValue()+1);
                        someCube = cubes[i][o][p];
                    }
                }
            }
        }

            for(int o = 1;o<7;o++){
                for(int i = 1;i<9;i++){
                    if(rand() % 100>20+raiseCounter){
                        cubes[i][o][1]=nullptr;
                    }else{
                        int x = 400-48*5+i*48;
                        int y = 300-48*4+o*48;
                        cubes[i][o][1] = new cube(x,y,
                                                  cube::intToCubeType(rand()%8)
                                                  ,someCube->scene(),-13.0);
                    }
                }
            }

        audioInstance->playSFXBufferB(QUrl("qrc:/audio/stageUp.wav"));
        raiseCounter++;
    }
}
