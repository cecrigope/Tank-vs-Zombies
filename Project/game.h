#ifndef GAME
#define GAME

#include <QGraphicsScene>
#include <QGraphicsView>

class Game{
public:
    Game();
    ~Game();
    void runPractice();
    void runZombie(int d);
    void start();
    void draw();
};

#endif // GAME

