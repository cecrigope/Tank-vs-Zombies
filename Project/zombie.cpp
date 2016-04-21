#include "zombie.h"
#include "player.h"
#include "score.h"
#include "game.h"

#include <typeinfo>     //used for collision
#include <QTimer>       //timer used for movement
#include <QApplication>
#include <QProcess>

//global variables
extern int sHeight;     //scene height
extern int sWidth;      //scene width
extern Player *player1; //player variable
extern int zombieCount; //keeping the count of the zombies
extern Score *score;    //instance of the score
extern QTimer *gameTimer;   //timer for the game
extern int zombieDiff;      //keeping the difficuly of the game
extern Game *game;          //instance of the game
extern QMediaPlayer* bulletSound;   //sound of the bullet


//timer variable
QTimer *moveTimer = new QTimer;

Zombie::Zombie():QObject(),QGraphicsRectItem(){
    //direction variable (for zombies)
    direct = 0;

    //random number within scene
    int randx = rand() % sWidth;
    int randy = rand() % sHeight;

    //making sure randx and rany are on the edges of scene
    while(randx > 0 && randx < sWidth - 5 && randy > 0 && randy < sHeight - 5){
        randx = rand() % sWidth;
        randy = rand() % sHeight;
    }

    //setting the position of the zombie
    this->setPos(randx,randy);

    //color of zombie
    QBrush brush (Qt::green);
    this->setBrush(brush);

    //moving the zombies
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));

    //choosing the speed of the game
    if(zombieDiff == 1){
        speed = 8;
    }
    else if(zombieDiff == 2){
        speed = 5;
    }

    //starting the timer
    moveTimer->start(speed);
}

//movement of zombies to follow player
void Zombie::move(){

     if((x()<player1->x()) && (y()<player1->y())){
        zombieCollision();
        setPos(x()+.7, y() + .7);
        zombieCollision();
        collision();
        deleteZombie();
        direct=1;
    }
    if((x()>player1->x()) && (y()<player1->y())){
        zombieCollision();
        setPos(x()-.7,y()+.7);
        zombieCollision();
        collision();
        deleteZombie();
        direct=2;
    }
    if((x()<player1->x()) && (y()>player1->y())){
        zombieCollision();
        setPos(x()+.7, y() -.7);
        zombieCollision();
        collision();
        deleteZombie();
        direct=3;
    }
    if((x()>player1->x()) && (y()>player1->y())){
        zombieCollision();
        setPos(x()-.7,y()-.7);
        zombieCollision();
        collision();
        deleteZombie();
        direct=4;
    }


}

//delete zombie
void Zombie::deleteZombie(){
    if(y() > sHeight ){
        delete this;
        zombieCount--;
    }
    if(y()<0){
        delete this;
        zombieCount--;
    }
    if(x()<0){
        delete this;
        zombieCount--;
    }
    if(x() > sWidth){
        delete this;
        zombieCount--;
    }

}

//collision
void Zombie::collision(){
    QList<QGraphicsItem *> colliding = collidingItems();
    for(int i=0, n=colliding.size();i<n;++i){

        //collision between zombie and player
        if(typeid(*(colliding[i])) == typeid(Player)){
            //stopping the game
            gameTimer->stop();
            moveTimer->stop();

            //deleting
            delete gameTimer;
            delete moveTimer;
            delete player1;
            delete game;
            delete score;
            delete scene();

            //restarting the game
            qApp->closeAllWindows();
            QStringList args = QApplication::arguments();
            args.removeFirst();
            QCoreApplication::quit();
            QProcess::startDetached(QApplication::applicationFilePath(), args);
        }
    }
}

//collisiong between two zombies
void Zombie::zombieCollision(){
    QList<QGraphicsItem *> colliding = collidingItems();
    for(int i=0, n=colliding.size();i<n;++i){
        if(typeid(*colliding[i]) == typeid(Zombie)){
            if(direct==1){
                this->setPos(x()-5, y() - 5);
                colliding[i]->setPos(colliding[i]->x()+5,colliding[i]->y()+5);
            }
            if(direct==2){
                this->setPos(x()+5,y()-5);
                 colliding[i]->setPos(colliding[i]->x()-5,colliding[i]->y()+5);
            }
            if(direct==3){
                this->setPos(x()-5,y()+5);
                 colliding[i]->setPos(colliding[i]->x()+5,colliding[i]->y()-5);
            }
            if(direct==4){
                this->setPos(x()+5,y()+5);
                colliding[i]->setPos(colliding[i]->x()-5,colliding[i]->y()-5);
            }
        }
    }

}

Zombie::~Zombie(){
}

