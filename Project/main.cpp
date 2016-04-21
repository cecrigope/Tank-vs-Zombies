#include <QApplication>
#include <QProcess>
#include <QDebug>

//include to run the game
#include "game.h"

Game *game;

int main(int argc, char *argv[])
{

        QApplication a(argc, argv);

        //initiating game variable
        game = new Game;
        game->start();

        return a.exec();

}



