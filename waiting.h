#ifndef WAITING_H
#define WAITING_H

#include <QDialog>
#include "socketthread.h"

namespace Ui {
class waiting;
}

class waiting : public QDialog
{
    Q_OBJECT

public:
    explicit waiting(QString, SocketThread *, QTimer *, QWidget *parent = 0);
    ~waiting();

private:
    Ui::waiting *ui;
    QString t1;
    QTimer *timer;
    SocketThread *thread;

private slots:
    void startGame(QString, QString);
};

#endif // WAITING_H
