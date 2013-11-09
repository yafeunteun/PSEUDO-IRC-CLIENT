#include "client.h"
#include <QHostAddress>


Client* Client::s_instance = 0;

Client* Client::Instance()
{
    if(s_instance == 0)
    {
        s_instance = new Client;
    }

    return s_instance;
}




Client::Client(QObject *parent)
    : QObject(parent)
{
}

void Client::connect(QString hostname, quint16 port)
{
    QHostAddress host;
    host.setAddress(hostname);
    m_socket = new QTcpSocket;

    m_socket->connectToHost(hostname, port);

}


QTcpSocket* Client::getSocket(void) const
{
    return m_socket;
}


void Client::onDataReceived()
{
    using namespace FROMSERVER;
    QByteArray data;
    data = this->getSocket()->readAll();

    Frame frame(data);


    if(frame.getId() >= 200 || frame.getId() == 0)           // Error code || success
    {
        Command *c = Invoker::Instance()->getCommand(frame.getId());
        if(c != NULL)
            c->throwError(frame.getCode());
        return;
    }

    QString msg = frame.getArgList().join(' ');
    Message* m;
    switch (frame.getCode()) {
    //case C_APUBMSG: m = new apubmsg(argList); break;
    //case C_APRIVMSG: m = new aprivmsg(argList); break;
    //case C_AOP: m = new aop(argList); break;
    //case C_ATOPIC: m = new atopic(argList); break;
    //case C_ANICK: m = new anick(argList); break;
    //case C_ALEAVE: m = new aleave(argList); break;
    //case C_AKICK: m = new akick(argList); break;
    //case C_ABAN: m = new aban(argList); break;
    //case C_RWALL: m = new rwall(argList); break;
    case C_AJOIN: m = new ajoin(msg); break;
    default:return ;
    }

    m->execute();

    delete m;
}
