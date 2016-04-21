 #include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "zombie.h"

#include <QTimer>       //needed to declare a timer
#include <typeinfo>     //needed to check collision
#include <QMediaPlayer>

//global variables
extern int dir;         //holding the direction of the tank
extern Score *score;    //score object (used to increase score)
extern int zombieCount;
extern int zombieDiff;


QTimer *timer = new QTimer(); //declaring a timer to move bullets

Bullet::Bullet():QObject(),QGraphicsRectItem(){

    //adding color to the bullet
    QBrush brush (Qt::red);
    this->setBrush(brush);

    //bullet going down
    if(dir == 1){
        //creating the bullet
        setRect(0,0,10,50);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveDown()));
    }
    //bullet going up
    else if(dir == 2){
        //creating the bullet
        setRect(0,0,10,50);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveUp()));

    }
    //bullet going left
    else if(dir == 3){
        //creating the bullet
        setRect(0,0,50,10);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveLeft()));

    }
    //bullet going right
    else if(dir == 4 || dir == 0){
        //creating the bullet
        setRect(0,0,50,10);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveRight()));
    }

    if(zombieDiff == 2){
        timer->start(0.85);
    }
    else{
        timer->start(1);
    }

}

//moving the bullet up
void Bullet::moveUp(){
    setPos(x(), y() - 1);
    //deleting bullet if it goes off screen
    if(y() < 0){
        delete this;
    }
    collision();
}

//moving the bullet down
void Bullet::moveDown(){
    setPos(x(), y() + 1);
    //deleting bullet if it goes off screen
    if(y() > scene()->height()){
        delete this;
    }
    collision();
}

//moving the bullet left
void Bullet::moveLeft(){
    setPos(x() - 1, y());
    //deleting bullet if it goes off screen
    if(x() < 0){
        delete this;
    }
    //checking collision of objects
    collision();
}

//moving the bullet right
void Bullet::moveRight(){
    setPos(x() + 1, y());
    //deleting bullet if it goes off screen
    if(x() > scene()->width()){
        delete this;
    }
    //checking collision of objects
    collision();
}


//checking for collision
void Bullet::collision(){
    //creating list of colliding items with respect to Bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){

        //if bullet collides with enemy, destroy both and increase score
        if(typeid(*(colliding_items[i])) == typeid(Enemy)){

            //increasing score
            score->practiceScore();

            //removing both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            //delete them both
            delete colliding_items[i];
            delete this;
        }

        //if bullet collides with zombie, destroy both and increase score
        if(typeid(*(colliding_items[i])) == typeid(Zombie)){

            //decreasing zombie count
            zombieCount--;

            //increasing score
            score->zombieScore();

            //removing both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            //delete them both
            delete colliding_items[i];
            delete this;

        }
        //if bullet collides with bullet
        else if(typeid(*colliding_items[i]) == typeid(Bullet)){
            scene()->removeItem(this);
            delete this;
        }
    }
}

//destructor
Bullet::~Bullet(){
}

