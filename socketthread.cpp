#include "socketthread.h"
#include <sstream>
#include <cstring>

using namespace std;

SocketThread::SocketThread(QString ip, QObject *parent)
{
    socket = new QTcpSocket();
    socket->connectToHost(ip, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
}

void SocketThread::sendMess(QString s)
{
    s.append(QChar(23));
    socket->write(s.toLocal8Bit());
}

void SocketThread::newMessage() {
    if(QTcpSocket *s = dynamic_cast<QTcpSocket *> (sender())) {
        message.append(s->readAll());
        if(!message.contains(QChar(23)))
            return;
        QStringList l = message.split(QChar(23));
        message = l.takeLast();
        for(int i = 0; i < l.size();i++) {
            string tmpS = l[i].toStdString();
            stringstream stream(tmpS);
            int a, num, num2;
            stream >> a;

            if(a == 1 || a == 2) {

            if(a == 2) {

                double b, c;
                stream >> num >> num2 >> b >> c;
                emit(movePlayer(num, num2, b, c));
            }
            else if(a == 1) {
                double b, c;
                stream >> num >> b >> c;
                emit(drawLine(num, b, c));
            }
            }
            else if(a == 3 || a == 4) {
                emit playerN(a - 2);
            }
            else if(a == 5) {
                double b, c;
                stream >> b >> c;
                emit ballMv(b, c);
            }
            else if(a == 10) {
                string t1, t2;
                stream >> t1 >> t2;
                QString qt = QString::fromStdString(t1), qt2 = QString::fromStdString(t2);
                qDebug() << qt << qt2 << "game is starting";
                emit startGame(qt, qt2);
            }
            else if(a == 11)
                emit nameAccepted();
            else if(a == 12)
                emit changeTurn();
        }
    }
}
