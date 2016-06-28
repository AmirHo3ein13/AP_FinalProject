#include "server.h"
#include <sstream>
#include <cstring>

using namespace std;

Server::Server() : server(new QTcpServer)
{
    this->t1 = "n"; this->t2 = "n";
    server->listen(QHostAddress::Any, 1234);
    qDebug() << server->serverAddress();
    qDebug() << server->serverAddress().toString() << server->serverPort();
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void Server::newConnection()
{
    while(server->hasPendingConnections()) {
        if(num == 0) {
            qDebug() << "c!";
            num =1;
            c1 = server->nextPendingConnection();
            connect(c1, SIGNAL(readyRead()), this, SLOT(newMessage()));
            connect(c1, SIGNAL(disconnected()), this, SLOT(disconnected()));

        }
        else if(num == 1) {
            qDebug() << "c@";
            num = 2;
            c2 = server->nextPendingConnection();
            connect(c2, SIGNAL(readyRead()), this, SLOT(newMessage()));
            connect(c2, SIGNAL(disconnected()), this, SLOT(disconnected()));
        }
    }
}

void Server::newMessage()
{
    if(QTcpSocket *c = dynamic_cast<QTcpSocket*> (sender())) {
        data[c].append(c->readAll());
        if(!data[c].contains(QChar(23)))
            return;
        QStringList l = data[c].split(QChar(23));
        data[c] = l.takeLast();
        foreach(QString s, l) {
            string sss = s.toStdString();
            stringstream ss(sss);
            int a;
            ss >> a;
            if(a == 2 || a == 5 || a == 12) {
                s.append(QChar(23));
                c1->write(s.toLocal8Bit());
                c2->write(s.toLocal8Bit());
            }
            else if(a == 7) { //team selection
                if(num == 1 && t1 == "n") {
                    string str;
                    ss >> str;
                    t1 = QString::fromStdString(str);
                    QString s = "11";
                    s.append(QChar(23));
                    c1->write(s.toLocal8Bit());
                }
                else if(num == 2) {
                    string str;
                    ss >> str;
                    t2 = QString::fromStdString(str);
                    if(t2 == t1) {
//                        QString s = "0";
//                        s.append(QChar(23));
//                        c2->write(s.toLocal8Bit());
                    }
                    else {
                        QString s = "11";
                        s.append(QChar(23));
                        c2->write(s.toLocal8Bit());
                        s = "10" + t1 + " " + t2;
                        s.append(QChar(23));
                        c1->write(s.toLocal8Bit());
                        c2->write(s.toLocal8Bit());
                        s = "3 ";
                        s.append(QChar(23));
                        c1->write(s.toLocal8Bit());
                        s = "4 ";
                        s.append(QChar(23));
                        c2->write(s.toLocal8Bit());
                        return;
                    }
                }
            }
            else {
                if(c != c1 && c1->state() == QTcpSocket::ConnectedState) {
                    s.append(QChar(23));
                    c1->write(s.toLocal8Bit());
                }
                else if(c != c2 && c2->state() == QTcpSocket::ConnectedState) {
                    s.append(QChar(23));
                    c2->write(s.toLocal8Bit());
                }
            }
        }
    }
}

void Server::disconnected()
{
    num--;
    t1 = t2 = "n";
}

