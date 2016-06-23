#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QString>

class SocketThread : public QThread
{
    Q_OBJECT
public:
    explicit SocketThread(QObject *parent = 0);
    void run();
    void sendMess(QString);

private:
    QTcpSocket *socket;

signals:
    void movePlayer(double, double);
    void drawLine(double, double);

private slots:
    void newMessage();

private:
    QString message;

public slots:
};

#endif // SOCKETTHREAD_H
