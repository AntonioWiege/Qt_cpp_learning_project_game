#include "game.h"

#include <QApplication>

game * game_instance;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    game_instance = new game();
    game_instance->play();

    return a.exec();
}

