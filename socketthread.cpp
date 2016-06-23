#include "socketthread.h"
#include <sstream>

using namespace std;

SocketThread::SocketThread(QObject *parent)
{

}

void SocketThread::run()
{
    socket->connectToHost("0.0.0.0", 12345);
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
    exec();
}

void SocketThread::sendMess(QString s)
{
    socket->write(s.toLocal8Bit());
}

void SocketThread::newMessage()
{
    if(QTcpSocket *s = dynamic_cast<QTcpSocket *> (sender())) {
        message.append(s->readAll());
        if(!message.contains(QChar(23)))
            return;
        QStringList l = message.split(QChar(23));
        message = l.takeLast();
        foreach(QString str, l) {
            string tmpS = str.toStdString();
            stringstream stream(tmpS);
            int a;
            double b, c;
            stream >> a >> b >> c;
            if(a == 1)
                emit(movePlayer(b, c));
            else if(a == 2)
                emit(drawLine(b, c));
        }
    }
}

