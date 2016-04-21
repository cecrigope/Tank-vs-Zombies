#ifndef PLAYER
#define PLAYER

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMediaPlayer>


class Player:public QObject,public QGraphicsRectItem{

    Q_OBJECT

public:
    Player();
    ~Player();
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

public slots:
    void spawn();
    void spawnZombies();
    void timerEvent();

private:
    bool moving_Up,moving_Down,moving_Left,moving_Right;
    int playerPos;
};

#endif // TANK
