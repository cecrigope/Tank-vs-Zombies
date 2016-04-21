#include "score.h"

#include <QFont>
extern int maxZombie;
extern int zombieSize;
extern int zombieDiff;

Score::Score (QGraphicsItem *parent): QGraphicsTextItem(parent){
    //initialize the score to 0
    score = 0;

    //initializing temp
    temp = 0;
    //draw the text
    setPlainText(QString("Score: ") + QString::number(score));

    //setting the default color and font
    setDefaultTextColor(Qt::green);
    setFont(QFont("times", 16));
}

//displaying score for practice mode
void Score::practiceScore(){
    //incrementing score
    score++;

    //reprinting the updated message
    setPlainText(QString("Score: ") + QString::number(score) + QString("\t\t\tPractice Mode **Use arrow keys to move and spacebar to shoot** Practice Mode"));
}

//displaying score for zombie game
void Score::zombieScore(){
    //incrementing score
    score += 100;
    temp+=100;

    //enhancing the game
    increaseZombie();

    //reprintig updated message
    setPlainText(QString("Score: ") + QString::number(score));

}

//setting score to zero
void Score::setZero(){
    //decreasing score
    score = 0;

    //reprinting updated message
    setPlainText(QString("Score: ") + QString::number(score));

}

//destructor
Score::~Score(){
}

//increasing zombie
void Score::increaseZombie(){
    if(temp == 2500 && zombieDiff == 1){
        temp = 0;

        if(maxZombie <= 15){
        zombieSize += 2.5 ;
        maxZombie += 1;
        }

    }
}

