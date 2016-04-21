#include "player2.h"
#include "bullet.h"

//global variable
int direct = 0;
int choice = 0;
Bullet *bullet;

void Player2::keyPressEvent(QKeyEvent *keyPress){
    //moving left
    if(keyPress->key()==Qt::Key_1){
        setPos(x() - 10, y());
        direct = 1;
    }

    //moving right
    else if(keyPress->key() == Qt::Key_3){
        setPos(x() + 10, y());
        direct = 2;
    }

    //moving up
    else if(keyPress->key() == Qt::Key_5){
        setPos(x(), y() - 10);
        direct = 3;
    }

    //moving down
    else if(keyPress->key() == Qt::Key_2){
        setPos(x(), y() + 10);
        direct = 4;
    }

    //shooting
    if(keyPress->key() == Qt::Key_Shift){
        bullet = new Bullet;
        bullet->setPos(x(), y());
        scene()->addItem(bullet);
    }
}

int Player2::direction(){
    if(direct == 1){
        choice = 1;
    }
    else if(direct == 2){
        choice = 2;
    }
    else if(direct == 3){
        choice = 3;
    }
    else if(direct == 4){
        choice = 4;
    }
    else{
        choice = 0;
    }

    return 0;
}
