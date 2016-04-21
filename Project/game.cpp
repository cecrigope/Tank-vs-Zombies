#include "game.h"   //including header file
#include "player.h"
#include "enemy.h"
#include "score.h"

#include <QTimer>               //Timer for spawning
#include <QGraphicsTextItem>    //displaying message
#include <QMessageBox>          //In order to display messages
#include <QPushButton>          //For Push Buttons
#include <QApplication>
#include <QProcess>

//variable for the scene
QGraphicsScene *scene;
//variable for the view
QGraphicsView *view;
//holding the score
Score *score;
//variable for tank
Player *player1;
//variable for timer holding the game
QTimer *gameTimer;
//variable for timer holding for the player
QTimer *playerTimer;

//variable for the scene and height
int sHeight;
int sWidth;

//variable for zombie count
int zombieCount;

//variable for holding the max zombie count
int maxZombie;

//variable holding difficulty for zombie
int zombieDiff;

//variable holding game speed
int gameSpeed;
//variable holding the speed of the player
int velocity=3;


Game::Game(){

    //defining sHeight and sWidth
    sHeight = 710;
    sWidth = 1300;

    //defining zombie count
    zombieCount = 0;

    //creating scene
    scene = new QGraphicsScene;

    //creating view
    view = new QGraphicsView;

    //taking off the scroll bar
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setting the size of the view and the scene
    view->setFixedSize(sWidth, sHeight);
    scene->setSceneRect(0,0,sWidth,sHeight);
}

void Game::start(){
    //clearing the scene
    scene->clear();

    //message box to ask to begin game
    QMessageBox messageBox;
    messageBox.setWindowTitle("Main Menu");
    QPushButton *exitButton = messageBox.addButton("Exit", QMessageBox::RejectRole);        //making an exit button
    QPushButton *practiceButton = messageBox.addButton("Practice", QMessageBox::YesRole);   //button for practice mode
    QPushButton *gameButton = messageBox.addButton("Zombie Game", QMessageBox::NoRole);     //button for game mode

    messageBox.exec();

    //if practice button is clicked
    if(messageBox.clickedButton() == practiceButton){
        //starting the practice game
        runPractice();
    }
    //if gameButton is clicked
    else if(messageBox.clickedButton() == gameButton){
        //message box for the zombie game
        QMessageBox msgBox;
        msgBox.setWindowTitle("Game Menu");
        QPushButton *normalButton = msgBox.addButton("Normal Mode", QMessageBox::YesRole);
        QPushButton *insaneButton = msgBox.addButton("Insane Mode", QMessageBox::NoRole);
        QPushButton *returnButton = msgBox.addButton("Back", QMessageBox::RejectRole);
        msgBox.exec();

        //running a normal game
        if(msgBox.clickedButton() == normalButton){
            //running the zombie game in normal difficulty
            runZombie(1);
        }
        //running insane game
        else if(msgBox.clickedButton() == insaneButton){
            //running the zombie game with insane difficulty
            runZombie(2);
        }
        //exiting
        else if(msgBox.clickedButton() == returnButton){
            //restarting the game
            qApp->closeAllWindows();
            QStringList args = QApplication::arguments();
            args.removeFirst();
            QCoreApplication::quit();
            QProcess::startDetached(QApplication::applicationFilePath(), args);
        }
    }
    //if exit button is clicked
    else if(messageBox.clickedButton() == exitButton){
        //deleting everything
        delete gameTimer;
        delete player1;
        delete this;
        delete score;
        delete scene;
        exit(0);
    }
}

//drawing the game
void Game::draw(){
    //scene->clear();

    //setting the color of the view
    QBrush brush (Qt::black);
    view->setBackgroundBrush(brush);

    //player1
    player1=new Player;

    //adding the player to the scene
    scene->addItem(player1);

    //setting dimensions for the player
    player1->setRect(0,0,50,50);
    player1->setPos(300, scene->height() / 2);

    //color of the player
    QBrush brushPlayer(Qt::blue);
    player1->setBrush(brushPlayer);

    //setting up focus on player for mobility
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player1->setFocus();

    //showing the view
    view->setScene(scene);
    view->show();
}

//practice round
void Game::runPractice(){

    //calling the draw function
    draw();

    //spawning enemies
    gameTimer = new QTimer;
    playerTimer=new QTimer;
    QObject::connect(gameTimer, SIGNAL(timeout()), player1, SLOT(spawn()));
      QObject::connect(playerTimer,SIGNAL(timeout()),player1,SLOT(timerEvent()));
    gameTimer->start(2000);
    playerTimer->start(velocity);

    //displaying score
    score = new Score;
    scene->addItem(score);
}

//zombie game
void Game::runZombie(int difficulty){
    //calling the draw function
    draw();

    //spawning zombies
    gameTimer = new QTimer;
    playerTimer=new QTimer;
    QObject::connect(gameTimer, SIGNAL(timeout()), player1, SLOT(spawnZombies()));
    QObject::connect(playerTimer,SIGNAL(timeout()),player1,SLOT(timerEvent()));
    //setting difficulty
    //normal mode
    if(difficulty == 1){
        gameSpeed = 500;
        zombieDiff = 1;
        maxZombie = 10;
    }
    //insane mode
    else if(difficulty == 2){
        gameSpeed = 100;
        zombieDiff = 2;
        maxZombie = 10;
    }

    //game time speed
    gameTimer->start(gameSpeed);
    playerTimer->start(velocity);

    //displaying score
    score = new Score;
    scene->addItem(score);
}

//destructor
Game::~Game(){
}
