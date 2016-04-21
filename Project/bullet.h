#ifndef BULLET_H_
#define BULLET_H_

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsScene>

class Bullet:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    Bullet();
    ~Bullet();
public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

private:
    void collision();
};


#endif // BULLET

