#include "socketthread.h"
#include <sstream>
#include <cstring>

using namespace std;

SocketThread::SocketThread(QObject *parent)
{
    socket = new QTcpSocket();
}

void SocketThread::run()
{
    socket->connectToHost("127.0.0.1", 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
    exec();
}

void SocketThread::sendMess(QString s)
{
    //qDebug() << "sending";
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
            qDebug() << l[i];
            stringstream stream(tmpS);
            int a, num;
            stream >> a;

            if(a == 1 || a == 2) {
            double b, c;
            stream >> num >> b >> c;
            if(a == 2)
                emit(movePlayer(num, b, c));
            else if(a == 1) {
                emit(drawLine(num, b, c));
            }
            }
            else {
                emit playerN(a - 2);
            }
        }
    }
}
