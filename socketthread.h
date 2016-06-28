#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QTcpSocket>

class SocketThread : public QObject
{
    Q_OBJECT
public:
    explicit SocketThread(QString ip, QObject *parent = 0);
    void sendMess(QString);
    QTcpSocket *socket;
    QString message;

signals:
    void movePlayer(int, int, double, double);
    void drawLine(int, double, double);
    void playerN(int);
    void ballMv(double, double);
    void startGame(QString s, QString s2);
    void nameAccepted();
    void changeTurn();

private slots:
    void newMessage();

public slots:
};

#endif // SOCKETTHREAD_H
