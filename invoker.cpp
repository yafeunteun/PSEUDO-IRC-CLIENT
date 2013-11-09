#include "invoker.h"
#include "widget.h"
#include "client.h"

#include <iostream>

using namespace std;

Invoker* Invoker::s_instance = 0;

Invoker* Invoker::Instance()
{
    if(s_instance == 0)
        s_instance = new Invoker;

    return s_instance;
}

Invoker::Invoker()
{
    m_history.reserve(128);
}

Invoker::~Invoker()
{
    this->clear();
}

void Invoker::clear()
{
    for ( unsigned int i = 0; i < m_history.size(); ++i )
    {
        delete m_history[i];
    }
    m_history.clear();
}


void Invoker::storeAndExecute(Command* cmd)
{

    quint8 _code = cmd->getCode();
    quint16 _id = cmd->getId();
    quint16 _size = cmd->getSize();
    QString args(cmd->getArgs());

    cout <<"before replace : "<<args.size()<<endl;
    args.replace(QChar(' '), QChar('\n'));
    cout <<"after replace : "<<args.size()<<endl;
    //args.resize(_size);
    args[_size-3] = QChar('\n'); // fait déconner !
    _size++; // we just have added \n character

   // cout<<args.toStdString()<<endl;

    //cout <<args.size()<<endl;


    //cout <<sizeof(_size)<<":"<< _size<<endl;


    m_history[_id] = cmd;


    QByteArray data((char*)&_size, 2);
    data.append((char*)&_id, 2);
    data.append((char*)&_code, 1);
    data.append(args);

    Client* c = Client::Instance();
    QTcpSocket* stream = c->getSocket();
    stream->write(data);

    Widget * w = Widget::Instance();
    w->getInputArea()->clear();

    cout <<"args.size()"<<endl;

}

Command* Invoker::getCommand(quint16 commandId)
{
    return m_history[commandId];
}
