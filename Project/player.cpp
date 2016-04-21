#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "zombie.h"
#include "score.h"

#include <QDebug>

//holding the direction of the tank
int dir = 0;

//global variables
extern int zombieCount;
extern int maxZombie;
extern int sHeight;
extern int sWidth;

QMediaPlayer* bulletSound = new QMediaPlayer;

int zombieSize; //setting the size of the zombie

//constructor
Player::Player(){
    //initialzing movement bool
    moving_Up = false;
    moving_Down = false;
    moving_Left = false;
    moving_Right = false;
    playerPos = 1;
    zombieSize = 30;

    //defining bullet sound
    bulletSound->setMedia(QUrl("qrc:/soundEffects/bulletSound.mp3"));
    bulletSound->setVolume(35);
}

//for movement
void Player::timerEvent(){

    if(moving_Down){
        //checking to stay in screen
        if(y() + 51 < sHeight){
          setPos(x(),y()+playerPos);
          dir = 1;
        }
    }
    if(moving_Up){
        //checking to stay on screen
         if(y() - 1 > 0){
          setPos(x(),y()-playerPos);
          dir = 2;
         }
    }
    if(moving_Left){
        //checking to stay in screen
        if(x() - 1 > 0){
         setPos(x()-playerPos,y());
         dir = 3;
        }
    }
    if(moving_Right){
        //checking to stay in screen
        if(x() + 51 < sWidth){
         setPos(x()+playerPos,y());
         dir =  4;
        }

    }
}

//key was pressed
void Player::keyPressEvent(QKeyEvent *keyEvent){
    //key press events for movement
    switch(keyEvent->key()){
    case Qt::Key_A:
        moving_Left=true;
        break;

    case Qt::Key_D:
        moving_Right=true;
        break;

    case Qt::Key_W:
        moving_Up=true;
        break;

    case Qt::Key_S:
        moving_Down=true;
        break;
    }

     //shootin bullets
     if(keyEvent->key()==Qt::Key_Space){
        //bullet spawning
        Bullet *bullet = new Bullet();
        if(dir == 1 || dir == 2){
            bullet->setPos(x() + 20, y());
        }
        else {
            bullet->setPos(x(), y() + 20);
        }
        scene()->addItem(bullet);

        //playing bullet sound
        if(bulletSound->state() == QMediaPlayer::PlayingState){
            bulletSound->setPosition(0);
        }
        else if(bulletSound->state() == QMediaPlayer::StoppedState){
            bulletSound->play();
        }
     }
    //exiting the game
    if(keyEvent->key()==Qt::Key_Escape){
        exit(0);
    }

}

//button is realesed
void Player::keyReleaseEvent(QKeyEvent *keyEvent){
    switch(keyEvent->key()){\
    case Qt::Key_A:
        moving_Left=false;
        break;

    case Qt::Key_D:
        moving_Right=false;
        break;

    case Qt::Key_W:
        moving_Up=false;
        break;

    case Qt::Key_S:
        moving_Down=false;
        break;
    }
}

//spawning the enemy
void Player::spawn(){
    Enemy *enemy = new Enemy;
    scene()->addItem(enemy);
}

//spawning the zombies
void Player::spawnZombies(){
    if(zombieCount < maxZombie){
        Zombie *zombie = new Zombie;

        //sets the size of the zombie
        zombie->setRect(0,0,zombieSize,zombieSize);

        //increasing zombie count
        zombieCount++;

        scene()->addItem(zombie);
    }
}

//destructor
Player::~Player(){
}


