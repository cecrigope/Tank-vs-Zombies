#include "enemy.h"
#include "player.h"
#include "score.h"
#include "game.h"

#include <typeinfo>
#include <QTimer>
#include <QProcess>
#include <QApplication>

//global variables
extern Player* player1;   //player
extern Score *score;    //score
extern QTimer* gameTimer;   //gameTimer
extern int sHeight;     //scene height
extern int sWidth;      //scene width
extern Game* game;
extern QMediaPlayer* bulletSound;

//declaring a timer variable
QTimer *timer1 = new QTimer();  //zombie moving time

Enemy::Enemy():QObject(),QGraphicsRectItem(){
    //giving the zombie dimensions
    this->setRect(0,0,20,20);

    //giving the zombies a colors
    QBrush brush(Qt::red);
    this->setBrush(brush);

    //creating a random position for starting zombie/enemy
    int randx = rand() % sWidth - 10;
    int randy = rand() % sHeight - 10;
    while(randx > 20 && randx < sWidth - 20 && randy > 20 && randx < sHeight - 20){
        randx = rand() % sWidth - 10;
        randy = rand() % sHeight - 10;
    }
    //setting the position of the zombie
    this->setPos(randx, randy);


    if(randx <= 650){
        //top left, enemy moves down
        if(randy <= 710/2){
            connect(timer1,SIGNAL(timeout()), this, SLOT(moveDown()));
        }
        //bottom left, enemy moves up
        else if(randy >= 532){
            connect(timer1, SIGNAL(timeout()), this, SLOT(moveUp()));
        }
        //middle left, enemy moves right
        else{
            connect(timer1, SIGNAL(timeout()), this, SLOT(moveRight()));
        }
    }

    else if(randx >= 650){
        //top right, enemy moves down
        if(randy <= 710/2){
            connect(timer1,SIGNAL(timeout()), this, SLOT(moveDown()));
        }
        //bottom right, enemy moves up
        else if(randy >= 532){
            connect(timer1, SIGNAL(timeout()), this, SLOT(moveUp()));
        }
        //middle right, enemy moves left
        else{
            connect(timer1, SIGNAL(timeout()), this, SLOT(moveLeft()));
        }
    }

    //timer for movemenet of object
    timer1->start(20);
}

//moving the zombie
void Enemy::moveDown(){
    setPos(x(), y() + 1);
    deleteEnemy();
    collision();
}

void Enemy::moveUp(){
    setPos(x(), y() - 1);
    deleteEnemy();
    collision();
}

void Enemy::moveLeft(){
    setPos(x() - 1, y());
    deleteEnemy();
    collision();
}

void Enemy::moveRight(){
    setPos(x() + 1, y());
    deleteEnemy();
    collision();
}

void Enemy::deleteEnemy(){
    //deleting item if goes off the screen
    if(y() > sHeight){
        delete(this);
    }
    else if(x() > sWidth){
        delete(this);
    }
    else if(x() < 0){
        delete(this);
    }
    else if(y() < 0){
        delete(this);
    }
}

void Enemy::collision(){
    //creating list of colliding items with respect to Zombie
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){

        //Zombie collides with player
        if(typeid(*(colliding_items[i])) == typeid(Player)){
            //stopping the game
            gameTimer->stop();
            timer1->stop();

            //deleting
            delete gameTimer;
            delete timer1;
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

//destructor
Enemy::~Enemy(){
}

