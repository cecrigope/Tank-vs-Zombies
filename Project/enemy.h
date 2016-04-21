#ifndef ENEMY
#define ENEMY

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsScene>

class Enemy:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    Enemy();
    ~Enemy();
public slots:
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveUp();

private:
    void deleteEnemy();
    void collision();
};


#endif // ZOMBIE

