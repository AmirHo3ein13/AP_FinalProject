#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QHash>


class Server : public QThread
{
    Q_OBJECT
public:
    Server();

private:
    QString t1, t2;
    int num = 0;
    QTcpServer *server;
    QTcpSocket *c1, *c2;
    QHash<QTcpSocket*, QString> data;

private slots:
    void newConnection();
    void newMessage();
    void disconnected();
};

#endif // SERVER_H
