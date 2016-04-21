#ifndef ZOMBIE
#define ZOMBIE

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsScene>

class Zombie:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    Zombie();
    ~Zombie();

public slots:
    void move();

private:
    void collision();
    void zombieCollision();
    void deleteZombie();
    int speed;
    int direct;
};



#endif // ZOMBIE

