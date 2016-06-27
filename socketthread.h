#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QTcpSocket>

class SocketThread : public QObject
{
    Q_OBJECT
public:
    explicit SocketThread(QObject *parent = 0);
    void sendMess(QString);
    QTcpSocket *socket;
    QString message;

signals:
    void movePlayer(int, double, double);
    void drawLine(int, double, double);
    void playerN(int);

private slots:
    void newMessage();

public slots:
};

#endif // SOCKETTHREAD_H
