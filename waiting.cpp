#include "waiting.h"
#include "ui_waiting.h"
#include "game.h"
#include <QImage>

waiting::waiting(QString t1, SocketThread *thread, QTimer *timer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waiting)
{
    this->timer = timer;
    this->thread = thread;
    connect(thread, SIGNAL(startGame(QString, QString)), this, SLOT(startGame(QString, QString)));
    this->t1 = t1;
    ui->setupUi(this);
}

waiting::~waiting()
{
    delete ui;
}

void waiting::startGame(QString t1, QString t2)
{
    Game *g = new Game(this->thread, this->timer, t1, t2);
    this->close();
}
