#ifndef SCORE
#define SCORE

#include <QGraphicsTextItem>

//score has to inherit QGraphicsTextItem
class Score: public QGraphicsTextItem{

public:
    Score(QGraphicsItem *parent = 0);
    ~Score();
    void practiceScore();
    void zombieScore();
    void setZero();
    void increaseZombie();

private:
    int score;
    int temp;
};

#endif // SCORE

